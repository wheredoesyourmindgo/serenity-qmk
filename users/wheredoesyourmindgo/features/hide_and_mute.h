// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

bool hide_and_mute(uint16_t keycode, keyrecord_t* record, uint16_t hide_and_mute_keycode);

#ifdef __cplusplus
}
#endif
