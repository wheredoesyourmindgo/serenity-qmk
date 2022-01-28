// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include QMK_KEYBOARD_H

typedef struct {
  uint16_t keycode;
  uint16_t modded_keycode;
} custom_gui_key_t;

extern const custom_gui_key_t custom_gui_keys[];
extern uint8_t NUM_CUSTOM_GUI_KEYS;

bool process_custom_gui_keys(uint16_t keycode, keyrecord_t *record);
