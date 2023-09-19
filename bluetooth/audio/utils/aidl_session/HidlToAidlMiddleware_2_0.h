/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android/hardware/bluetooth/audio/2.0/types.h>

#include "../session/BluetoothAudioSession.h"

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

using SessionType_2_0 =
    ::android::hardware::bluetooth::audio::V2_0::SessionType;
using PortStatusCallbacks_2_0 =
    ::android::bluetooth::audio::PortStatusCallbacks;
using AudioConfig_2_0 =
    ::android::hardware::bluetooth::audio::V2_0::AudioConfiguration;

class HidlToAidlMiddleware_2_0 {
 public:
  static bool IsAidlAvailable();

  static bool IsSessionReady(const SessionType_2_0& session_type);

  static uint16_t RegisterControlResultCback(
      const SessionType_2_0& session_type,
      const PortStatusCallbacks_2_0& cbacks);

  static void UnregisterControlResultCback(const SessionType_2_0& session_type,
                                           uint16_t cookie);

  static const AudioConfig_2_0 GetAudioConfig(
      const SessionType_2_0& session_type);

  static bool StartStream(const SessionType_2_0& session_type);

  static void StopStream(const SessionType_2_0& session_type);

  static bool SuspendStream(const SessionType_2_0& session_type);

  static bool GetPresentationPosition(const SessionType_2_0& session_type,
                                      uint64_t* remote_delay_report_ns,
                                      uint64_t* total_bytes_readed,
                                      timespec* data_position);

  static void UpdateTracksMetadata(
      const SessionType_2_0& session_type,
      const struct source_metadata* source_metadata);

  static size_t OutWritePcmData(const SessionType_2_0& session_type,
                                const void* buffer, size_t bytes);

  static size_t InReadPcmData(const SessionType_2_0& session_type, void* buffer,
                              size_t bytes);
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
