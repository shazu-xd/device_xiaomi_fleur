/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android/hardware/bluetooth/audio/2.1/types.h>

#include "../session/BluetoothAudioSession.h"

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

using SessionType_2_1 =
    ::android::hardware::bluetooth::audio::V2_1::SessionType;
using AudioConfig_2_1 =
    ::android::hardware::bluetooth::audio::V2_1::AudioConfiguration;

class HidlToAidlMiddleware_2_1 {
 public:
  static const AudioConfig_2_1 GetAudioConfig(
      const SessionType_2_1& session_type);
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
