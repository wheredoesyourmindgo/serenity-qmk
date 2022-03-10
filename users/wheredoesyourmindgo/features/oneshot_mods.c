// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "oneshot_mods.h"
#include "wheredoesyourmindgo.h"


void oneshot_mods_layer_state(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            break;
        //  for any other layers, or the default layer
        default:
            // Cancel One Shot Mods (if active) is necessary when switching to layers OTHER than base layer. This will prevent an issue where the keyboard might get stuck in a layer.
            if (ONESHOT_MODS_ACTIVE) {
                clear_oneshot_mods();
            }
            break;
    }
}

bool process_oneshot_mods(uint16_t keycode, keyrecord_t* record) {
    // This fixes issue where two shifted alphas occur (instead of one) after using sentence_end tap function
    // if (ONESHOT_MODS_ACTIVE & MOD_BIT(KC_LSFT) && record->event.pressed) {
    //     clear_oneshot_mods();
    // }
    switch (keycode) {
        case XOSM_LSFT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LSFT));
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
            }
            return false;
        case XOSM_LGUI:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                add_oneshot_mods(MOD_BIT(KC_LGUI));
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case XOSM_LALT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                add_oneshot_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;
        case XOSM_LCTL:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL));
                add_oneshot_mods(MOD_BIT(KC_LCTL));
            } else {
                unregister_mods(MOD_BIT(KC_LCTL));
            }
            return false;
        // The R*Mod variants are not working. Just using the L*Mod variants in keymap with High* layers
        case XOSM_RSFT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RSFT));
                add_oneshot_mods(MOD_BIT(KC_RSFT));
            } else {
                unregister_mods(MOD_BIT(KC_RSFT));
            }
            return false;
        case XOSM_RGUI:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RGUI));
                add_oneshot_mods(MOD_BIT(KC_RGUI));
            } else {
                unregister_mods(MOD_BIT(KC_RGUI));
            }
            return false;
        case XOSM_RALT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RALT));
                add_oneshot_mods(MOD_BIT(KC_RALT));
            } else {
                unregister_mods(MOD_BIT(KC_RALT));
            }
            return false;
        case XOSM_RCTL:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RCTL));
                add_oneshot_mods(MOD_BIT(KC_RCTL));
            } else {
                unregister_mods(MOD_BIT(KC_RCTL));
            }
            return false;
        case KC_ESC:
            if (record->event.pressed) {
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                    // Only fire escape special mode is not active
                    return false;
                }
            }
            break;
        case LT(LOWER, KC_ESC):
            if (record->event.pressed) {
                // Only on tap (ie. Not during LT(LOWER)
                if (record->tap.count > 0) {
                    // Cancel One Shot Mods (if active)
                    if (ONESHOT_MODS_ACTIVE) {
                        clear_oneshot_mods();
                        // Only fire escape special mode is not active
                        return false;
                    }
                }
            }
            break;
    }

    return true;
}
