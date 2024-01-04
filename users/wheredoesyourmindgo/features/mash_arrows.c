// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "mash_arrows.h"
#include "wheredoesyourmindgo.h"

bool process_mash_arrows(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) { return true; }

    switch (keycode) {
         case LT(HRDWR, KC_LEFT):
            if (record->tap.count > 0) {
            //   if (record->event.pressed) {
                  if (MODS_RALT || MODS_RGUI || MODS_RCTRL) {
                    // Un-register mods
                    if (MODS_RALT) {
                        tap_code16_unset_mod(KC_UP);
                    }
                    if (MODS_RGUI) {
                      tap_code16_unset_mod(KC_DOWN);
                    }
                    if (MODS_RCTRL) {
                        tap_code16_unset_mod(KC_RIGHT);
                    }
                    // No need to to call tap_code_unset_mod or tap_code_no_mod since mods unset above
                    tap_code(KC_LEFT);
                  } else {
                      return true;
                  }
                  return false;
            //   }
            }
            break;
        case RALT_T(KC_UP):
            if (record->tap.count > 0) {
                  if (MODS_RGUI || MODS_RCTRL || IS_LAYER_ON(HRDWR)) {
                    if (MODS_RGUI) {
                      tap_code16_unset_mod(KC_DOWN);
                    }
                    if (MODS_RCTRL) {
                        tap_code16_unset_mod(KC_RIGHT);
                    }
                    if (IS_LAYER_ON(HRDWR)) {
                        layer_off(HRDWR);
                        tap_code(KC_LEFT);
                    }
                    tap_code(KC_UP);
                  } else {
                      return true;
                  }
                  return false;
            }
            break;
        case RGUI_T(KC_DOWN):
            if (record->tap.count > 0) {
                  if (MODS_RALT || MODS_RCTRL || IS_LAYER_ON(HRDWR)) {
                    if (MODS_RALT) {
                      tap_code16_unset_mod(KC_UP);
                    }
                    if (MODS_RCTRL) {
                        tap_code16_unset_mod(KC_RIGHT);
                    }
                    if (IS_LAYER_ON(HRDWR)) {
                        layer_off(HRDWR);
                        tap_code(KC_LEFT);
                    }
                    tap_code(KC_DOWN);
                  } else {
                      return true;
                   }
                  return false;
            }
            break;
        case RCTL_T(KC_RIGHT):
                if (MODS_RALT || MODS_RGUI || IS_LAYER_ON(HRDWR)) {
                    if (MODS_RALT) {
                      tap_code16_unset_mod(KC_UP);
                    }
                    if (MODS_RGUI) {
                        tap_code16_unset_mod(KC_DOWN);
                    }
                    if (IS_LAYER_ON(HRDWR)) {
                        layer_off(HRDWR);
                        tap_code(KC_LEFT);
                    }
                    tap_code(KC_RIGHT);
                } else {
                    return true;
                }
                return false;
            break;
    }

  return true;
}
