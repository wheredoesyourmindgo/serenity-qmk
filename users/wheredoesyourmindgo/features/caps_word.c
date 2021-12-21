// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "caps_word.h"

bool process_caps_word(uint16_t keycode, keyrecord_t* record) {
  static bool caps_word_enabled = false;
  static bool shifted = false;
  static bool left_shifting = false;

  void cancel_caps_word(void) {
    // Disable caps word.
    caps_word_enabled = false;
    if (shifted) {
        if (left_shifting) {
            unregister_code(KC_RSFT);
        } else {
            unregister_code(KC_LSFT);
        }
    }
    shifted = false;
  }

  if (!caps_word_enabled) {
    // Pressing both shift keys at the same time enables caps word.
    if (((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
        == MOD_MASK_SHIFT) {
      clear_mods();
      clear_oneshot_mods();
      shifted = false;
      caps_word_enabled = true;
      return false;
    }
    return true;
  }

  if (!record->event.pressed) { return true; }

  if (!((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT)) {
    switch (keycode) {
      case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        // Earlier return if this has not been considered tapped yet.
        if (record->tap.count == 0) { return true; }
        // Get the base tapping keycode of a mod- or layer-tap key.
        keycode &= 0xff;
    }

    switch (keycode) {
      case KC_RSFT:
        left_shifting = false;
        return true;

      case KC_LSFT:
        left_shifting = true;
        return true;

      // Letter keys should be shifted.
      case KC_A ... KC_Z:
        if (!shifted) {
            if (left_shifting) {
                register_code(KC_RSFT);
            } else {
                register_code(KC_LSFT);
            }
        }
        shifted = true;
        return true;

      // Keycodes that continue caps word but shouldn't get shifted.
      case KC_1 ... KC_0:
      case KC_BSPC:
      case KC_MINS:
      case KC_UNDS:
      case KC_QUOT:
      // opening braces
      case KC_LPRN:
      case KC_LBRACKET:
      case KC_LCBR:
      case KC_LABK:
        if (shifted) {
            if (left_shifting) {
                unregister_code(KC_RSFT);
            } else {
                unregister_code(KC_LSFT);
            }
        }
        shifted = false;
        return true;

      // Just cancel caps word and don't send keycode.
    //   case KC_ESC:
    //     cancel_caps_word();
    //     return false;

      // Any other keycode disables caps word.
    }
  }

  cancel_caps_word();
  return true;
}
