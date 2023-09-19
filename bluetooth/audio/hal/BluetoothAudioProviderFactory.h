/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/bluetooth/audio/BnBluetoothAudioProviderFactory.h>

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

class BluetoothAudioProviderFactory : public BnBluetoothAudioProviderFactory {
 public:
  BluetoothAudioProviderFactory();

  ndk::ScopedAStatus openProvider(
      const SessionType session_type,
      std::shared_ptr<IBluetoothAudioProvider>* _aidl_return) override;

  ndk::ScopedAStatus getProviderCapabilities(
      const SessionType session_type,
      std::vector<AudioCapabilities>* _aidl_return) override;
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
