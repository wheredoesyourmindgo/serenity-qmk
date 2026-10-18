// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "symbol_rolls.h"

bool process_symbol_rolls(uint16_t keycode, keyrecord_t* record, uint8_t sym_layer) {
    if (!record->event.pressed) { return true; }
    if (!IS_LAYER_ON(sym_layer)) { return true; }

    // Tap these shifted symbols on press instead of holding them until release. Each shares a key
    // with an unshifted symbol (eg. { and [), so in a fast roll the second press would otherwise be
    // lost while the first is still held.
    switch (keycode) {
        case KC_TILDE:              // ~
        case KC_LT:                 // <
        case KC_GT:                 // >
        case KC_LEFT_CURLY_BRACE:   // {
        case KC_RIGHT_CURLY_BRACE:  // }
        case KC_QUESTION:           // ?
        case KC_PIPE:               // |
            tap_code16(keycode);
            // Skipping QMK's handling also skips using up a one-shot mod, so do it here. Held mods stay held.
            if (get_oneshot_mods()) {
                clear_oneshot_mods();
                send_keyboard_report();
            }
            return false;
    }

  return true;
}
