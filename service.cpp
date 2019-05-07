/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "AudioEffectHAL"

#include <android/hardware/audio/effect/2.0/IEffectsFactory.h>

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/LegacySupport.h>


#include "EffectsFactory.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

using ::android::hardware::audio::effect::V2_0::IEffectsFactory;
using ::android::hardware::audio::effect::V2_0::renesas::EffectsFactory;
using ::android::sp;

int main() {
    android::ProcessState::initWithDriver("/dev/vndbinder");

    configureRpcThreadpool(1, true /* callerWillJoin */);

    android::sp<IEffectsFactory> factory = new EffectsFactory();
    android::status_t status = factory->registerAsService();

    CHECK_EQ(status, android::OK) << "Failed to register IEffectsFactory interface.";

    joinRpcThreadpool();
}
