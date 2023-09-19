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

class LeAudioSoftwareAudioProvider : public BluetoothAudioProvider {
 public:
  LeAudioSoftwareAudioProvider();

  bool isValid(const SessionType& sessionType) override;

  ndk::ScopedAStatus startSession(
      const std::shared_ptr<IBluetoothAudioPort>& host_if,
      const AudioConfiguration& audio_config,
      const std::vector<LatencyMode>& latency_modes,
      DataMQDesc* _aidl_return);

 private:
  // audio data queue for software encoding
  std::unique_ptr<DataMQ> data_mq_;

  ndk::ScopedAStatus onSessionReady(DataMQDesc* _aidl_return) override;
};

class LeAudioSoftwareOutputAudioProvider : public LeAudioSoftwareAudioProvider {
 public:
  LeAudioSoftwareOutputAudioProvider();
};

class LeAudioSoftwareInputAudioProvider : public LeAudioSoftwareAudioProvider {
 public:
  LeAudioSoftwareInputAudioProvider();
};

class LeAudioSoftwareBroadcastAudioProvider
    : public LeAudioSoftwareAudioProvider {
 public:
  LeAudioSoftwareBroadcastAudioProvider();
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
