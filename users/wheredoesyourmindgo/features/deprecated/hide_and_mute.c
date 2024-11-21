// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "features/hide_and_mute.h"

bool hide_and_mute(uint16_t keycode, keyrecord_t* record, uint16_t hide_and_mute_keycode) {
    if (record->event.pressed) {
        static bool tapped = false;
        static uint16_t tap_timer = 0;
        if (keycode == hide_and_mute_keycode) {
            if (tapped && !timer_expired(record->event.time, tap_timer)) {
                // The key was double tapped.
                clear_mods();  // If needed, clear the mods.
                // hide window first, then mute
                tap_code16(LGUI(KC_H));  // Hide Active Window
                // KC_MUTE will toggle, additionally lower volume
                int i;
                for (i = 1; i <= 20; ++i) {
                    tap_code(KC_VOLD);
                }
            }
            tapped = true;
            tap_timer = record->event.time + TAPPING_TERM;
        } else {
            // On an event with any other key, reset the double tap state.
            tapped = false;
        }
    }
  return true;
}
