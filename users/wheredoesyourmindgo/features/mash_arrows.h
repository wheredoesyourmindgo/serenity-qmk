// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include QMK_KEYBOARD_H

/**
 * Mash Arrows — directional taps that play nice with held mods/layers
 *
 * Summary
 * -------
 * Allows arrow taps that intelligently clear conflicting held modifiers or a layer
 * (e.g., HRDWR) just for the tap, then performs the intended arrow key.
 *
 * Expected bindings
 * -----------------
 * - LT(HRDWR, KC_LEFT) : when tapped, send ← and clear RALT/RGUI/RCTRL as needed
 * - RALT_T(KC_UP)      : when tapped, send ↑ and clear RGUI/RCTRL/HRDWR as needed
 * - RGUI_T(KC_DOWN)    : when tapped, send ↓ and clear RALT/RCTRL/HRDWR as needed
 * - RCTL_T(KC_RIGHT)   : when tapped, send → and clear RALT/RGUI/HRDWR as needed
 *
 * Wiring
 * ------
 * Call from your `process_record_user` and return its result:
 *   if (!process_mash_arrows(keycode, record)) { return false; }
 */

bool process_mash_arrows(uint16_t keycode, keyrecord_t* record);
