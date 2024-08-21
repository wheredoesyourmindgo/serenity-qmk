// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "symbol_rolls.h"

bool process_symbol_rolls(uint16_t keycode, keyrecord_t* record, uint8_t sym_layer) {
    if (!record->event.pressed) { return true; }
    if (!IS_LAYER_ON(sym_layer)) { return true; }

    // Immediately un-register (shift) mods (don't wait for keypress release). This will prevent shifted symbols from happening during fast rolls on low(symbol) layer for keys that require a shift press followed by a key that doesn't, eg. /, \, [, and ].
    switch (keycode) {
        case KC_LT:
        case KC_GT:
        case KC_LEFT_CURLY_BRACE:
        case KC_RIGHT_CURLY_BRACE:
        case KC_QUESTION:
        case KC_PIPE:
        case KC_EXLM:
        case KC_AT:
        case KC_HASH:
        case KC_DLR:
        case KC_PERC:
        case KC_CIRC:
        case KC_AMPR:
        case KC_LPRN:
        case KC_RPRN:
        case KC_ASTR:
            tap_code16(keycode);
            uint8_t mod_state;
            mod_state = get_mods();
            unregister_mods(mod_state);
            return false;
    }

  return true;
}
