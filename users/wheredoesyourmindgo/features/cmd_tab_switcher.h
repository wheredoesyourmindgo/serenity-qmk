// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include QMK_KEYBOARD_H

/**
 * Cmd-Tab Switcher (macOS-style)
 *
 * Summary
 * -------
 * Emulates macOS Cmd+Tab app switcher with smooth “scrub” behavior.
 * - Starts switcher on first press
 * - Speeds up timeout while scrubbing left/right
 * - Cancels automatically after inactivity
 * - Plays nice with an encoder that holds RGUI (scrub) while LGUI is used for Cmd-Tab
 *
 * Keycodes (expected)
 * -------------------
 * - CMD_TAB_NXT : move right (Cmd+Tab)
 * - CMD_TAB_PRV : move left  (Cmd+Shift+Tab)
 * - OS_PRV_SPC / OS_NXT_SPC : mark “held” while space switching (adjusts timer)
 * - OS_EXPOSE   : when active, sends UpArrow to trigger Exposé/Mission Control
 *
 * Hooks to wire
 * -------------
 * In your keymap:
 *   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *     if (!process_cmd_tab_switcher(keycode, record)) return false;
 *     // ...rest...
 *     return true;
 *   }
 *
 *   void matrix_scan_user(void) {
 *     cmd_tab_switcher_matrix_scan_user();
 *     // ...rest...
 *   }
 *
 *   layer_state_t layer_state_set_user(layer_state_t state) {
 *     cmd_tab_switcher_layer_state(state);
 *     return state;
 *   }
 *
 * Configuration
 * -------------
 * #define cmd_tab_timer_default_dur 2000   // ms until switcher auto-cancels
 * #define cmd_tab_timer_fast_dur    600    // ms while scrubbing
 */

#define cmd_tab_timer_default_dur 2000
#define cmd_tab_timer_fast_dur    600

#define MODS_RGUI (get_mods() & MOD_BIT(KC_RGUI))
#define MODS_LSFT (get_mods() & MOD_BIT(KC_LSFT))
#define MODS_LGUI (get_mods() & MOD_BIT(KC_LGUI))

extern bool is_cmd_tab_active;
extern bool is_cmd_tab_held;
extern uint16_t cmd_tab_timer;
extern uint16_t cmd_tab_timer_timeout;

void cancel_cmd_shift(void);
void cmd_tab_previous(void);
void cmd_tab_next(void);
void cmd_tab_switcher_layer_state(layer_state_t state);
void cmd_tab_switcher_matrix_scan_user(void);
bool process_cmd_tab_switcher(uint16_t keycode, keyrecord_t* record);
