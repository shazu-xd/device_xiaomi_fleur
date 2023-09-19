/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "BTAudioProviderA2dpHW"

#include "A2dpOffloadAudioProvider.h"

#include <BluetoothAudioCodecs.h>
#include <BluetoothAudioSessionReport.h>
#include <android-base/logging.h>

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

A2dpOffloadEncodingAudioProvider::A2dpOffloadEncodingAudioProvider()
    : A2dpOffloadAudioProvider() {
  session_type_ = SessionType::A2DP_HARDWARE_OFFLOAD_ENCODING_DATAPATH;
}

A2dpOffloadDecodingAudioProvider::A2dpOffloadDecodingAudioProvider()
    : A2dpOffloadAudioProvider() {
  session_type_ = SessionType::A2DP_HARDWARE_OFFLOAD_DECODING_DATAPATH;
}

A2dpOffloadAudioProvider::A2dpOffloadAudioProvider() {}

bool A2dpOffloadAudioProvider::isValid(const SessionType& session_type) {
  return (session_type == session_type_);
}

ndk::ScopedAStatus A2dpOffloadAudioProvider::startSession(
    const std::shared_ptr<IBluetoothAudioPort>& host_if,
    const AudioConfiguration& audio_config,
    const std::vector<LatencyMode>& latency_modes, DataMQDesc* _aidl_return) {
  if (audio_config.getTag() != AudioConfiguration::a2dpConfig) {
    LOG(WARNING) << __func__ << " - Invalid Audio Configuration="
                 << audio_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }
  if (!BluetoothAudioCodecs::IsOffloadCodecConfigurationValid(
          session_type_, audio_config.get<AudioConfiguration::a2dpConfig>())) {
    LOG(WARNING) << __func__ << " - Invalid Audio Configuration="
                 << audio_config.toString();
    *_aidl_return = DataMQDesc();
    return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
  }
  return BluetoothAudioProvider::startSession(
      host_if, audio_config, latency_modes, _aidl_return);
}

ndk::ScopedAStatus A2dpOffloadAudioProvider::onSessionReady(
    DataMQDesc* _aidl_return) {
  *_aidl_return = DataMQDesc();
  BluetoothAudioSessionReport::OnSessionStarted(
      session_type_, stack_iface_, nullptr, *audio_config_, latency_modes_);
  return ndk::ScopedAStatus::ok();
}

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
