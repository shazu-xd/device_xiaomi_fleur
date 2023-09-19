/*
 * Copyright 2018 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "BluetoothAudioSession.h"

namespace android {
namespace bluetooth {
namespace audio {

class BluetoothAudioSessionReport {
 public:
  // The API reports the Bluetooth stack has started the session, and will
  // inform registered bluetooth_audio outputs
  static void OnSessionStarted(const SessionType& session_type,
                               const sp<IBluetoothAudioPort> host_iface,
                               const DataMQ::Descriptor* dataMQ,
                               const AudioConfiguration& audio_config) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->OnSessionStarted(host_iface, dataMQ, audio_config);
    }
  }
  // The API reports the Bluetooth stack has ended the session, and will
  // inform registered bluetooth_audio outputs
  static void OnSessionEnded(const SessionType& session_type) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->OnSessionEnded();
    }
  }
  // The API reports the Bluetooth stack has replied the result of startStream
  // or suspendStream, and will inform registered bluetooth_audio outputs
  static void ReportControlStatus(const SessionType& session_type,
                                  const bool& start_resp,
                                  const BluetoothAudioStatus& status) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type);
    if (session_ptr != nullptr) {
      session_ptr->ReportControlStatus(start_resp, status);
    }
  }
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace android
