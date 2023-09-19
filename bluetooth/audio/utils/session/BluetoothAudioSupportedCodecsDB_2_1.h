/*
 * Copyright 2020 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "BluetoothAudioSupportedCodecsDB.h"

#include <android/hardware/bluetooth/audio/2.1/types.h>

namespace android {
namespace bluetooth {
namespace audio {

std::vector<::android::hardware::bluetooth::audio::V2_1::PcmParameters>
GetSoftwarePcmCapabilities_2_1();
std::vector<::android::hardware::bluetooth::audio::V2_0::CodecCapabilities>
GetOffloadCodecCapabilities(
    const ::android::hardware::bluetooth::audio::V2_1::SessionType&
        session_type);

bool IsSoftwarePcmConfigurationValid_2_1(
    const ::android::hardware::bluetooth::audio::V2_1::PcmParameters&
        pcm_config);

bool IsOffloadCodecConfigurationValid(
    const ::android::hardware::bluetooth::audio::V2_1::SessionType&
        session_type,
    const ::android::hardware::bluetooth::audio::V2_0::CodecConfiguration&
        codec_config);

bool IsOffloadLeAudioConfigurationValid(
    const ::android::hardware::bluetooth::audio::V2_1::SessionType&
        session_type,
    const ::android::hardware::bluetooth::audio::V2_1::Lc3CodecConfiguration&
        le_audio_codec_config);
}  // namespace audio
}  // namespace bluetooth
}  // namespace android
