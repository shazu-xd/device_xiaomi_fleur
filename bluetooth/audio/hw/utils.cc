/*
 * Copyright 2019 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "BTAudioHalUtils"

#include "utils.h"

#include <android-base/logging.h>
#include <android-base/strings.h>
#include <log/log.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

namespace android {
namespace bluetooth {
namespace audio {
namespace utils {

std::unordered_map<std::string, std::string> ParseAudioParams(
    const std::string& params) {
  std::vector<std::string> segments = android::base::Split(params, ";");
  std::unordered_map<std::string, std::string> params_map;
  for (const auto& segment : segments) {
    if (segment.length() == 0) {
      continue;
    }
    std::vector<std::string> kv = android::base::Split(segment, "=");
    if (kv[0].empty()) {
      LOG(WARNING) << __func__ << ": Invalid audio parameter " << segment;
      continue;
    }
    params_map[kv[0]] = (kv.size() > 1 ? kv[1] : "");
  }
  return params_map;
}

std::string GetAudioParamString(
    std::unordered_map<std::string, std::string>& params_map) {
  std::ostringstream sout;
  for (const auto& ptr : params_map) {
    sout << "key: '" << ptr.first << "' value: '" << ptr.second << "'\n";
  }
  return sout.str();
}

}  // namespace utils
}  // namespace audio
}  // namespace bluetooth
}  // namespace android
