/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "BTAudioProviderHearingAid"

#include "HearingAidAudioProvider.h"

#include <BluetoothAudioCodecs.h>
#include <BluetoothAudioSessionReport.h>
#include <android-base/logging.h>

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

static constexpr uint32_t kPcmFrameSize = 4;  // 16 bits per sample / stereo
static constexpr uint32_t kPcmFrameCount = 128;
static constexpr uint32_t kRtpFrameSize = kPcmFrameSize * kPcmFrameCount;
static constexpr uint32_t kRtpFrameCount = 7;  // max counts by 1 tick (20ms)
static constexpr uint32_t kBufferSize = kRtpFrameSize * kRtpFrameCount;
static constexpr uint32_t kBufferCount = 1;  // single buffer
static constexpr uint32_t kDataMqSize = kBufferSize * kBufferCount;

HearingAidAudioProvider::HearingAidAudioProvider()
    : BluetoothAudioProvider(), data_mq_(nullptr) {
  LOG(INFO) << __func__ << " - size of audio buffer " << kDataMqSize
            << " byte(s)";
  std::unique_ptr<DataMQ> data_mq(
      new DataMQ(kDataMqSize, /* EventFlag */ true));
  if (data_mq && data_mq->isValid()) {
    data_mq_ = std::move(data_mq);
    session_type_ = SessionType::HEARING_AID_SOFTWARE_ENCODING_DATAPATH;
  } else {
    ALOGE_IF(!data_mq, "failed to allocate data MQ");
    ALOGE_IF(data_mq && !data_mq->isValid(), "data MQ is invalid");
  }
}
bool HearingAidAudioProvider::isValid(const SessionType& sessionType) {
  return (sessionType == session_type_ && data_mq_ && data_mq_->isValid());
}

ndk::ScopedAStatus HearingAidAudioProvider::startSession(
    const std::shared_ptr<IBluetoothAudioPort>& host_if,
    const AudioConfiguration& audio_config,
    const std::vector<LatencyMode>& latency_modes, DataMQDesc* _aidl_return) {
  if (audio_config.getTag() != AudioConfiguration::pcmConfig) {
    LOG(WARNING) << __func__ << " - Invalid Audio Configuration="
                 << audio_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }
  const auto& pcm_config = audio_config.get<AudioConfiguration::pcmConfig>();
  if (!BluetoothAudioCodecs::IsSoftwarePcmConfigurationValid(pcm_config)) {
    LOG(WARNING) << __func__ << " - Unsupported PCM Configuration="
                 << pcm_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }

  return BluetoothAudioProvider::startSession(
      host_if, audio_config, latency_modes, _aidl_return);
}

ndk::ScopedAStatus HearingAidAudioProvider::onSessionReady(
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
