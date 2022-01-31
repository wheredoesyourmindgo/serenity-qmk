// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "caps_sentence.h"

bool process_caps_sentence(uint16_t keycode, keyrecord_t* record, uint16_t CAPS_SENTENCE) {
  static bool caps_sentence_enabled = false;

  void cancel_caps_sentence(void) {
    // Disable caps sentence.
    caps_sentence_enabled = false;
  }

  if (!caps_sentence_enabled) {
    if (keycode
        == CAPS_SENTENCE) {
      clear_mods();
      clear_oneshot_mods();
      caps_sentence_enabled = true;
      return false;
    }
    return true;
  }

  if (!record->event.pressed) { return true; }
  if (keycode == CAPS_SENTENCE) { return false; }

  switch (keycode) {
    // don't strip out shift press
    // case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    // do strip out layer press
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
      // Earlier return if this has not been considered tapped yet.
      if (record->tap.count == 0) { return true; }
      // Get the base tapping keycode of a mod- or layer-tap key.
      keycode &= 0xff;
  }

  switch (keycode) {
    case KC_LSFT:
    case KC_RSFT:
      return true;

    // case label must be integer constant, see above
    // case CAPS_SENTENCE:
    //   return false;

    // Letter keys should be shifted.
    case KC_A ... KC_Z:
      tap_code16(LSFT(keycode));
      return false;

    // Keycodes that continue caps sentence but shouldn't get shifted.
    case KC_1 ... KC_0:
    case KC_BSPACE:
    case KC_MINUS:
    case KC_UNDERSCORE:
    case KC_QUOTE:
    // opening braces
    case KC_LEFT_PAREN:
    case KC_LBRACKET:
    case KC_LEFT_CURLY_BRACE:
    case KC_LEFT_ANGLE_BRACKET:
    // caps sentence specific
    case KC_SPACE:
    case KC_COMMA:
      return true;

    // Just cancel caps sentence and don't send keycode.
    //   case KC_ESC:
    //     cancel_caps_sentence();
    //     return false;

    // Any other keycode disables caps sentence.
  }

  cancel_caps_sentence();
  return true;
}
