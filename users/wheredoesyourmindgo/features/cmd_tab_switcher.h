// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include QMK_KEYBOARD_H

#define cmd_tab_timer_default_dur 1000;
#define cmd_tab_timer_fast_dur 600;

#define MODS_RGUI (get_mods() & MOD_BIT(KC_RGUI))

bool is_cmd_tab_active;
bool is_cmd_tab_held;
uint16_t cmd_tab_timer;
uint16_t cmd_tab_timer_timeout;

void cancel_cmd_shift(void);
void cmd_tab_previous(void);
void cmd_tab_next(void);
void cmd_tab_switcher_layer_state(layer_state_t state);
void cmd_tab_switcher_matrix_scan_user(void);
bool process_cmd_tab_switcher(uint16_t keycode, keyrecord_t* record);
