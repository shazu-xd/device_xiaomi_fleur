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

class LeAudioOffloadAudioProvider : public BluetoothAudioProvider {
 public:
  LeAudioOffloadAudioProvider();

  bool isValid(const SessionType& sessionType) override;

  ndk::ScopedAStatus startSession(
      const std::shared_ptr<IBluetoothAudioPort>& host_if,
      const AudioConfiguration& audio_config,
      const std::vector<LatencyMode>& latency_modes,
      DataMQDesc* _aidl_return);

 private:
  ndk::ScopedAStatus onSessionReady(DataMQDesc* _aidl_return) override;
};

class LeAudioOffloadOutputAudioProvider : public LeAudioOffloadAudioProvider {
 public:
  LeAudioOffloadOutputAudioProvider();
};

class LeAudioOffloadInputAudioProvider : public LeAudioOffloadAudioProvider {
 public:
  LeAudioOffloadInputAudioProvider();
};

class LeAudioOffloadBroadcastAudioProvider
    : public LeAudioOffloadAudioProvider {
 public:
  LeAudioOffloadBroadcastAudioProvider();
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
