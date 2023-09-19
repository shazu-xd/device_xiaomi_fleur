/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <aidl/android/hardware/bluetooth/audio/BnBluetoothAudioProvider.h>
#include <aidl/android/hardware/bluetooth/audio/LatencyMode.h>
#include <aidl/android/hardware/bluetooth/audio/SessionType.h>
#include <fmq/AidlMessageQueue.h>

using ::aidl::android::hardware::common::fmq::MQDescriptor;
using ::aidl::android::hardware::common::fmq::SynchronizedReadWrite;
using ::android::AidlMessageQueue;

using MqDataType = int8_t;
using MqDataMode = SynchronizedReadWrite;
using DataMQ = AidlMessageQueue<MqDataType, MqDataMode>;
using DataMQDesc = MQDescriptor<MqDataType, MqDataMode>;

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

class BluetoothAudioProvider : public BnBluetoothAudioProvider {
 public:
  BluetoothAudioProvider();
  ndk::ScopedAStatus startSession(
      const std::shared_ptr<IBluetoothAudioPort>& host_if,
      const AudioConfiguration& audio_config,
      const std::vector<LatencyMode>& latency_modes,
      DataMQDesc* _aidl_return);
  ndk::ScopedAStatus endSession();
  ndk::ScopedAStatus streamStarted(BluetoothAudioStatus status);
  ndk::ScopedAStatus streamSuspended(BluetoothAudioStatus status);
  ndk::ScopedAStatus updateAudioConfiguration(
      const AudioConfiguration& audio_config);
  ndk::ScopedAStatus setLowLatencyModeAllowed(bool allowed);

  virtual bool isValid(const SessionType& sessionType) = 0;

 protected:
  virtual ndk::ScopedAStatus onSessionReady(DataMQDesc* _aidl_return) = 0;
  static void binderDiedCallbackAidl(void* cookie_ptr);

  ::ndk::ScopedAIBinder_DeathRecipient death_recipient_;

  std::shared_ptr<IBluetoothAudioPort> stack_iface_;
  std::unique_ptr<AudioConfiguration> audio_config_ = nullptr;
  SessionType session_type_;
  std::vector<LatencyMode> latency_modes_;
  bool is_binder_died = false;
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
