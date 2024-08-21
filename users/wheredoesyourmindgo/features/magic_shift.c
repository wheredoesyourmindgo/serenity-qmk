// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "magic_shift.h"
#include "wheredoesyourmindgo.h"

bool process_magic_shift(uint16_t keycode, keyrecord_t* record) {

  // Track whether alt-shift is being used so that we don't get stuck in NUMNAV/AUX layers when using dedicated shift keys with mods
  static bool alt_lshift_active = false;
  static bool alt_rshift_active = false;

  switch (keycode) {
    // right half
    case LT(HRDWR, KC_LEFT):
      if (record->event.pressed) {
        // Only on hold during LT(HRDWR, KC_LEFT)
        if (!(record->tap.count > 0)) {
          if (MODS_RCTRL || MODS_RALT || MODS_RGUI) {
              layer_on(BASE);
              alt_rshift_active = true;
              register_mods(MOD_BIT(KC_RSFT));
              // abort retro tapping
              // retro_tapping_counter++;
              return false;
          }
        }
      } else {
          if (MODS_RSFT && alt_rshift_active) {
              alt_rshift_active = false;
              unregister_mods(MOD_BIT(KC_RSFT));
          }
      }
      break;
    case KC_RGUI:
        if (record->event.pressed) {
            if (IS_LAYER_ON(HRDWR)) {
                layer_off(HRDWR);
                alt_rshift_active = true;
                register_mods(MOD_BIT(KC_RSFT));
            }
        } else {
            if (MODS_RSFT && !MODS_RCTRL && !MODS_RALT && MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;
    case RGUI_T(KC_DOWN):
        if (record->event.pressed) {
            // Only on hold during RGUI_T(KC_DOWN)
            if (!(record->tap.count > 0)) {
                if (IS_LAYER_ON(HRDWR)) {
                    layer_off(HRDWR);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            }
        } else {
            if (MODS_RSFT && !MODS_RCTRL && !MODS_RALT && MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;
    case KC_RALT:
        if (record->event.pressed) {
            if (IS_LAYER_ON(HRDWR)) {
                layer_off(HRDWR);
                alt_rshift_active = true;
                register_mods(MOD_BIT(KC_RSFT));
            }
        } else {
            if (MODS_RSFT && !MODS_RCTRL && MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;
    case RALT_T(KC_UP):
        if (record->event.pressed) {
            // Only on hold during RALT_T(KC_UP)
            if (!(record->tap.count > 0)) {
                if (IS_LAYER_ON(HRDWR)) {
                    layer_off(HRDWR);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            }
        } else {
            if (MODS_RSFT && !MODS_RCTRL && MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;
    case KC_RCTL:
         if (record->event.pressed) {
            if (IS_LAYER_ON(HRDWR)) {
                layer_off(HRDWR);
                alt_rshift_active = true;
                register_mods(MOD_BIT(KC_RSFT));
            }
        } else {
            if (MODS_RSFT && MODS_RCTRL && !MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;
    case RCTL_T(KC_RIGHT):
        if (record->event.pressed) {
            // Only on hold during RCTL_T(KC_RIGHT)
            if (!(record->tap.count > 0)) {
                if (IS_LAYER_ON(HRDWR)) {
                    layer_off(HRDWR);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            }
        } else {
            if (MODS_RSFT && MODS_RCTRL && !MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                alt_rshift_active = false;
                unregister_mods(MOD_BIT(KC_RSFT));
                layer_on(HRDWR);
            }
        }
        break;

    // left half
    case MO(AUX):
        if (record->event.pressed) {
            // Only on hold during MO(AUX)
            if (!(record->tap.count > 0)) {
                if (MODS_LCTRL || MODS_LALT || MODS_LGUI) {
                    layer_on(BASE);
                    alt_lshift_active = true;
                    register_mods(MOD_BIT(KC_LSFT));
                    // abort retro tapping
                    // retro_tapping_counter++;
                    return false;
                }
            }
        } else {
            if (MODS_LSFT && alt_lshift_active) {
                alt_lshift_active = false;
                unregister_mods(MOD_BIT(KC_LSFT));
            }
        }
        break;
    case KC_LGUI:
        if (record->event.pressed) {
            if (IS_LAYER_ON(AUX)) {
                layer_off(AUX);
                alt_lshift_active = true;
                register_mods(MOD_BIT(KC_LSFT));
            }
        } else {
            if (MODS_LSFT && !MODS_LCTRL && !MODS_LALT && MODS_LGUI && alt_lshift_active) {
                alt_lshift_active = false;
                unregister_mods(MOD_BIT(KC_LSFT));
                layer_on(AUX);
            }
        }
      break;
    case KC_LALT:
      if (record->event.pressed) {
          if (IS_LAYER_ON(AUX)) {
              layer_off(AUX);
              alt_lshift_active = true;
              register_mods(MOD_BIT(KC_LSFT));
          }
      } else {
          if (MODS_LSFT && !MODS_LCTRL && MODS_LALT && !MODS_LGUI && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
              layer_on(AUX);
          }
      }
      break;
    case KC_LCTL:
      if (record->event.pressed) {
          if (IS_LAYER_ON(AUX)) {
              layer_off(AUX);
              alt_lshift_active = true;
              register_mods(MOD_BIT(KC_LSFT));
          }
      } else {
          if (MODS_LSFT && MODS_LCTRL && !MODS_LALT && !MODS_LGUI && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
              layer_on(AUX);
          }
      }
      break;

  }
  return true;
}
