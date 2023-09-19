/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

enum led_type {
    BACKLIGHT,
    RED,
    GREEN,
    BLUE,
    WHITE,
};

class Lights : public BnLights {
public:
    Lights();

    ndk::ScopedAStatus setLightState(int id, const HwLightState& state) override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* types) override;

private:
    void setSpeakerLightLocked(const HwLightState& state);
    void handleSpeakerBatteryLocked();
    void handleBacklight(const HwLightState& state);

    bool setLedBreath(led_type led, uint32_t value);
    bool setLedBrightness(led_type led, uint32_t value);

    bool IsLit(uint32_t color);
    uint32_t RgbaToBrightness(uint32_t color);
    bool WriteToFile(const std::string& path, uint32_t content);

    bool mWhiteLed;
    HwLightState mNotification;
    HwLightState mBattery;
};

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
