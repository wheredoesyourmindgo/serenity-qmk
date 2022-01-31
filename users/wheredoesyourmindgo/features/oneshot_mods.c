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
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LALT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LGUI | MOD_LALT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LGUI | MOD_LALT));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LGUI | MOD_LCTL));
                    } else if (ONESHOT_MODS_LALT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LALT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LGUI));
                    } else if (ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LALT));
                    } else if (ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LSFT | MOD_LCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_LSFT);
                }
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
            }
            return false;
        case XOSM_LGUI:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_LSFT && ONESHOT_MODS_LALT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LSFT | MOD_LALT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LSFT && ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LSFT | MOD_LALT));
                    } else if (ONESHOT_MODS_LSFT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LSFT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LALT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LALT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LSFT));
                    } else if (ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LALT));
                    } else if (ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LGUI | MOD_LCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_LGUI);
                }
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case XOSM_LALT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LSFT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LGUI | MOD_LSFT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LGUI | MOD_LSFT));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LGUI | MOD_LCTL));
                    } else if (ONESHOT_MODS_LSFT && ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LSFT | MOD_LCTL));
                    } else if (ONESHOT_MODS_LGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LGUI));
                    } else if (ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LSFT));
                    } else if (ONESHOT_MODS_LCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LALT | MOD_LCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_LALT);
                }
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;
        case XOSM_LCTL:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LALT && ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LGUI | MOD_LALT | MOD_LSFT));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LGUI | MOD_LALT));
                    } else if (ONESHOT_MODS_LGUI && ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LGUI | MOD_LSFT));
                    } else if (ONESHOT_MODS_LALT && ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LALT | MOD_LSFT));
                    } else if (ONESHOT_MODS_LGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LGUI));
                    } else if (ONESHOT_MODS_LALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LALT));
                    } else if (ONESHOT_MODS_LSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_LCTL | MOD_LSFT));
                    }
                } else {
                    set_oneshot_mods(MOD_LCTL);
                }
            } else {
                unregister_mods(MOD_BIT(KC_LCTL));
            }
            return false;
        // The R*Mod variants are not working. Just using the L*Mod variants in keymap with High* layers
        case XOSM_RSFT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RSFT));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RALT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RGUI | MOD_RALT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RGUI | MOD_RALT));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RGUI | MOD_RCTL));
                    } else if (ONESHOT_MODS_RALT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RALT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RGUI));
                    } else if (ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RALT));
                    } else if (ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RSFT | MOD_RCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_RSFT);
                }
            } else {
                unregister_mods(MOD_BIT(KC_RSFT));
            }
            return false;
        case XOSM_RGUI:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RGUI));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_RSFT && ONESHOT_MODS_RALT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RSFT | MOD_RALT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RSFT && ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RSFT | MOD_RALT));
                    } else if (ONESHOT_MODS_RSFT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RSFT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RALT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RALT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RSFT));
                    } else if (ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RALT));
                    } else if (ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RGUI | MOD_RCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_RGUI);
                }
            } else {
                unregister_mods(MOD_BIT(KC_RGUI));
            }
            return false;
        case XOSM_RALT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RALT));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RSFT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RGUI | MOD_RSFT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RGUI | MOD_RSFT));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RGUI | MOD_RCTL));
                    } else if (ONESHOT_MODS_RSFT && ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RSFT | MOD_RCTL));
                    } else if (ONESHOT_MODS_RGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RGUI));
                    } else if (ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RSFT));
                    } else if (ONESHOT_MODS_RCTL) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RALT | MOD_RCTL));
                    }
                } else {
                    set_oneshot_mods(MOD_RALT);
                }
            } else {
                unregister_mods(MOD_BIT(KC_RALT));
            }
            return false;
        case XOSM_RCTL:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RCTL));
                if (ONESHOT_MODS_ACTIVE) {
                    if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RALT && ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RGUI | MOD_RALT | MOD_RSFT));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RGUI | MOD_RALT));
                    } else if (ONESHOT_MODS_RGUI && ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RGUI | MOD_RSFT));
                    } else if (ONESHOT_MODS_RALT && ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RALT | MOD_RSFT));
                    } else if (ONESHOT_MODS_RGUI) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RGUI));
                    } else if (ONESHOT_MODS_RALT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RALT));
                    } else if (ONESHOT_MODS_RSFT) {
                        clear_oneshot_mods();
                        set_oneshot_mods((MOD_RCTL | MOD_RSFT));
                    }
                } else {
                    set_oneshot_mods(MOD_RCTL);
                }
            } else {
                unregister_mods(MOD_BIT(KC_RCTL));
            }
            return false;
        case KC_ESC:
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
