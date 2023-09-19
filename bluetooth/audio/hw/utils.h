/*
 * Copyright 2019 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>
#include <unordered_map>

namespace android {
namespace bluetooth {
namespace audio {
namespace utils {

// Creates a hash map based on the |params| string containing key and value
// pairs.  Pairs are expected in the form "key=value" separated by the ';'
// character.  Both ';' and '=' characters are invalid in keys or values.
// Examples:
//   "key0"                      -> map: [key0]=""
//   "key0=value0;key1=value1;"  -> map: [key0]="value0" [key1]="value1"
//   "key0=;key1=value1;"        -> map: [key0]="" [key1]="value1"
//   "=value0;key1=value1;"      -> map: [key1]="value1"
std::unordered_map<std::string, std::string> ParseAudioParams(
    const std::string& params);

// Dumps the contents of the hash_map to the log for debugging purposes.
// If |map| is not NULL, all entries of |map| will be dumped, otherwise
// nothing will be dumped. Note that this function does not take the ownership
// of the |map|.
std::string GetAudioParamString(
    std::unordered_map<std::string, std::string>& params_map);

}  // namespace utils
}  // namespace audio
}  // namespace bluetooth
}  // namespace android
