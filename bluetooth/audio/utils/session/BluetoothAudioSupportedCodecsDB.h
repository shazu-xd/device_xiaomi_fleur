/*
 * Copyright 2018 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <android/hardware/bluetooth/audio/2.0/types.h>

namespace android {
namespace bluetooth {
namespace audio {

using ::android::hardware::bluetooth::audio::V2_0::CodecCapabilities;
using ::android::hardware::bluetooth::audio::V2_0::CodecConfiguration;
using ::android::hardware::bluetooth::audio::V2_0::PcmParameters;
using ::android::hardware::bluetooth::audio::V2_0::SessionType;

std::vector<PcmParameters> GetSoftwarePcmCapabilities();
std::vector<CodecCapabilities> GetOffloadCodecCapabilities(
    const SessionType& session_type);

bool IsSoftwarePcmConfigurationValid(const PcmParameters& pcm_config);
bool IsOffloadCodecConfigurationValid(const SessionType& session_type,
                                      const CodecConfiguration& codec_config);

}  // namespace audio
}  // namespace bluetooth
}  // namespace android
