/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "BTAudioProviderA2dpSW"

#include "A2dpSoftwareAudioProvider.h"

#include <BluetoothAudioCodecs.h>
#include <BluetoothAudioSessionReport.h>
#include <android-base/logging.h>

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

// Here the buffer size is based on SBC
static constexpr uint32_t kPcmFrameSize = 4;  // 16 bits per sample / stereo
// SBC is 128, and here we choose the LCM of 16, 24, and 32
static constexpr uint32_t kPcmFrameCount = 96;
static constexpr uint32_t kRtpFrameSize = kPcmFrameSize * kPcmFrameCount;
// The max counts by 1 tick (20ms) for SBC is about 7. Since using 96 for the
// PCM counts, here we just choose a greater number
static constexpr uint32_t kRtpFrameCount = 10;
static constexpr uint32_t kBufferSize = kRtpFrameSize * kRtpFrameCount;
static constexpr uint32_t kBufferCount = 2;  // double buffer
static constexpr uint32_t kDataMqSize = kBufferSize * kBufferCount;

A2dpSoftwareEncodingAudioProvider::A2dpSoftwareEncodingAudioProvider()
    : A2dpSoftwareAudioProvider() {
  session_type_ = SessionType::A2DP_SOFTWARE_ENCODING_DATAPATH;
}

A2dpSoftwareDecodingAudioProvider::A2dpSoftwareDecodingAudioProvider()
    : A2dpSoftwareAudioProvider() {
  session_type_ = SessionType::A2DP_SOFTWARE_DECODING_DATAPATH;
}

A2dpSoftwareAudioProvider::A2dpSoftwareAudioProvider()
    : BluetoothAudioProvider(), data_mq_(nullptr) {
  LOG(INFO) << __func__ << " - size of audio buffer " << kDataMqSize
            << " byte(s)";
  std::unique_ptr<DataMQ> data_mq(
      new DataMQ(kDataMqSize, /* EventFlag */ true));
  if (data_mq && data_mq->isValid()) {
    data_mq_ = std::move(data_mq);
  } else {
    ALOGE_IF(!data_mq, "failed to allocate data MQ");
    ALOGE_IF(data_mq && !data_mq->isValid(), "data MQ is invalid");
  }
}

bool A2dpSoftwareAudioProvider::isValid(const SessionType& sessionType) {
  return (sessionType == session_type_ && data_mq_ && data_mq_->isValid());
}

ndk::ScopedAStatus A2dpSoftwareAudioProvider::startSession(
    const std::shared_ptr<IBluetoothAudioPort>& host_if,
    const AudioConfiguration& audio_config,
    const std::vector<LatencyMode>& latency_modes, DataMQDesc* _aidl_return) {
  if (audio_config.getTag() != AudioConfiguration::pcmConfig) {
    LOG(WARNING) << __func__ << " - Invalid Audio Configuration="
                 << audio_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }
  const PcmConfiguration& pcm_config =
      audio_config.get<AudioConfiguration::pcmConfig>();
  if (!BluetoothAudioCodecs::IsSoftwarePcmConfigurationValid(pcm_config)) {
    LOG(WARNING) << __func__ << " - Unsupported PCM Configuration="
                 << pcm_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }

  return BluetoothAudioProvider::startSession(
      host_if, audio_config, latency_modes, _aidl_return);
}

ndk::ScopedAStatus A2dpSoftwareAudioProvider::onSessionReady(
    DataMQDesc* _aidl_return) {
  if (data_mq_ == nullptr || !data_mq_->isValid()) {
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }
  *_aidl_return = data_mq_->dupeDesc();
  auto desc = data_mq_->dupeDesc();
  BluetoothAudioSessionReport::OnSessionStarted(
      session_type_, stack_iface_, &desc, *audio_config_, latency_modes_);
  return ndk::ScopedAStatus::ok();
}

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
