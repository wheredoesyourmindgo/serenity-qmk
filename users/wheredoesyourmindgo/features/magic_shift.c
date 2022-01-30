// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "magic_shift.h"
#include "wheredoesyourmindgo.h"

bool process_magic_shift(uint16_t keycode, keyrecord_t* record) {

  // Track whether alt-shift is being used so that we don't get stuck in lower/higher layers when using dedicated shift keys with mods
  static bool alt_lshift_active = false;
  static bool alt_rshift_active = false;

  switch (keycode) {
    // Higher (right side)
    case LT(HIGHER, KC_SPC):
      if (record->event.pressed) {
          if (MODS_RCTRL || MODS_RALT || MODS_RGUI) {
              layer_on(BASE);
              alt_rshift_active = true;
              register_mods(MOD_BIT(KC_RSFT));
              // abort retro tapping
              // retro_tapping_counter++;
              return false;
          }
          // Only during layer hold
          if (!(record->tap.count > 0)) {
              if (IS_LAYER_ON(LOWER)) {
                  layer_off(LOWER);
                  layer_on(OS);
                  return false;
              }
          }
      } else {
          if (MODS_RSFT && alt_rshift_active) {
              alt_rshift_active = false;
              unregister_mods(MOD_BIT(KC_RSFT));
          }
          if (IS_LAYER_ON(OS)) {
              layer_off(OS);
              layer_on(LOWER);
              return false;
          }
      }
      break;
    case KC_RGUI:
        case RGUI_T(KC_LEFT):
            if (record->event.pressed) {
                if (IS_LAYER_ON(HIGHER)) {
                    layer_off(HIGHER);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            } else {
                if (MODS_RSFT && !MODS_RCTRL && !MODS_RALT && MODS_RGUI && alt_rshift_active) {
                    alt_rshift_active = false;
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHER);
                }
            }
            break;
    case KC_RALT:
    case RALT_T(KC_DOWN):
            if (record->event.pressed) {
                if (IS_LAYER_ON(HIGHER)) {
                    layer_off(HIGHER);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            } else {
                if (MODS_RSFT && !MODS_RCTRL && MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                    alt_rshift_active = false;
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHER);
                }
            }
            break;
    case KC_RCTL:
    case RCTL_T(KC_UP):
            if (record->event.pressed) {
                if (IS_LAYER_ON(HIGHER)) {
                    layer_off(HIGHER);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                }
            } else {
                if (MODS_RSFT && MODS_RCTRL && !MODS_RALT && !MODS_RGUI && alt_rshift_active) {
                    alt_rshift_active = false;
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHER);
                }
            }
            break;

    // Lower (left side)
    case LT(LOWER, KC_ESC):
      if (record->event.pressed) {
        if (MODS_LCTRL || MODS_LALT || MODS_LGUI) {
            layer_on(BASE);
            alt_lshift_active = true;
            register_mods(MOD_BIT(KC_LSFT));
            // abort retro tapping
            // retro_tapping_counter++;
            return false;
        }
        // Only on tap (ie. Not during LT(LOWER)
        if (record->tap.count > 0) {
            // Only fire escape special mode is not active
            if (!ONESHOT_MODS_ACTIVE) {
                return true;
            }
            // Cancel One Shot Mods (if active)
            if (ONESHOT_MODS_ACTIVE) {
                clear_oneshot_mods();
            }
            return false;
        } else {
            if (IS_LAYER_ON(HIGHER)) {
                layer_off(HIGHER);
                layer_on(OS);
                return false;
            }
        }
      } else {
          if (MODS_LSFT && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
          }
          if (IS_LAYER_ON(OS)) {
              layer_off(OS);
              layer_on(HIGHER);
              return false;
          }
      }
      break;
    case KC_LGUI:
      if (record->event.pressed) {
          if (IS_LAYER_ON(LOWER)) {
              layer_off(LOWER);
              alt_lshift_active = true;
              register_mods(MOD_BIT(KC_LSFT));
          }
      } else {
          if (MODS_LSFT && !MODS_LCTRL && !MODS_LALT && MODS_LGUI && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
              layer_on(LOWER);
          }
      }
      break;
    case KC_LALT:
      if (record->event.pressed) {
          if (IS_LAYER_ON(LOWER)) {
              layer_off(LOWER);
              alt_lshift_active = true;
              register_mods(MOD_BIT(KC_LSFT));
          }
      } else {
          if (MODS_LSFT && !MODS_LCTRL && MODS_LALT && !MODS_LGUI && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
              layer_on(LOWER);
          }
      }
      break;
    case KC_LCTL:
      if (record->event.pressed) {
          if (IS_LAYER_ON(LOWER)) {
              layer_off(LOWER);
              alt_lshift_active = true;
              register_mods(MOD_BIT(KC_LSFT));
          }
      } else {
          if (MODS_LSFT && MODS_LCTRL && !MODS_LALT && !MODS_LGUI && alt_lshift_active) {
              alt_lshift_active = false;
              unregister_mods(MOD_BIT(KC_LSFT));
              layer_on(LOWER);
          }
      }
      break;

  }
  return true;
}
