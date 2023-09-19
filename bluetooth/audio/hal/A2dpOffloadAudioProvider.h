/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "BluetoothAudioProvider.h"

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

class A2dpOffloadAudioProvider : public BluetoothAudioProvider {
 public:
  A2dpOffloadAudioProvider();

  bool isValid(const SessionType& session_type) override;

  ndk::ScopedAStatus startSession(
      const std::shared_ptr<IBluetoothAudioPort>& host_if,
      const AudioConfiguration& audio_config,
      const std::vector<LatencyMode>& latency_modes,
      DataMQDesc* _aidl_return);

 private:
  ndk::ScopedAStatus onSessionReady(DataMQDesc* _aidl_return) override;
};

class A2dpOffloadEncodingAudioProvider : public A2dpOffloadAudioProvider {
 public:
  A2dpOffloadEncodingAudioProvider();
};

class A2dpOffloadDecodingAudioProvider : public A2dpOffloadAudioProvider {
 public:
  A2dpOffloadDecodingAudioProvider();
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
