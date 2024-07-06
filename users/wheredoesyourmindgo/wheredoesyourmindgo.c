#include "wheredoesyourmindgo.h"
// #include "features/caps_word.h"
// #include "features/caps_sentence.h"
#include "features/oneshot_mods.h"
#include "features/custom_shift_keys.h"
// #include "features/custom_gui_keys.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"
#include "features/mash_arrows.h"
#include "features/layer_lock.h"
#include "features/mo_ext.h"
// #include "features/hide_and_mute.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// extern int retro_tapping_counter;

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
bool process_tap_or_long_press_key(keyrecord_t *record, uint16_t long_press_keycode) {
    if (record->tap.count == 0) { // Key is being held.
        if (record->event.pressed) {
            tap_code16(long_press_keycode);
        }
        return false; // Skip default handling.
    }
    return true; // Continue default handling.
}

// Helper for custom backspace forward behavior
bool check_mods_sft_and_gui(void) {
    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();

    bool is_shift_active = (mods & MOD_MASK_SHIFT) || (oneshot_mods & MOD_MASK_SHIFT);
    bool is_gui_active = (mods & MOD_MASK_GUI) || (oneshot_mods & MOD_MASK_GUI);

    return is_shift_active && is_gui_active;
}

void tap_code16_no_mod(uint16_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    uint8_t w_mod_state;
    uint8_t o_mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state   = get_mods();
    w_mod_state = get_weak_mods();
    o_mod_state = get_oneshot_mods();
    if (mod_state || w_mod_state || o_mod_state) {
        // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
        del_mods(mod_state);
        del_weak_mods(w_mod_state);
        del_oneshot_mods(o_mod_state);
        send_keyboard_report();
        tap_code16(code);
        // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
        add_mods(mod_state);
        add_weak_mods(w_mod_state);
        set_oneshot_mods(o_mod_state);
        send_keyboard_report();
    } else {
        tap_code16(code);
    }
}

void tap_code_no_mod(uint8_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    uint8_t w_mod_state;
    uint8_t o_mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state   = get_mods();
    w_mod_state = get_weak_mods();
    o_mod_state = get_oneshot_mods();
    if (mod_state || w_mod_state || o_mod_state) {
        // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
        del_mods(mod_state);
        del_weak_mods(w_mod_state);
        del_oneshot_mods(o_mod_state);
        send_keyboard_report();
        tap_code16(code);
        // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
        add_mods(mod_state);
        add_weak_mods(w_mod_state);
        set_oneshot_mods(o_mod_state);
        send_keyboard_report();
    } else {
        tap_code(code);
    }
}

void tap_code16_unset_mod(uint16_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    uint8_t w_mod_state;
    uint8_t o_mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state   = get_mods();
    w_mod_state = get_weak_mods();
    o_mod_state = get_oneshot_mods();
    if (mod_state || w_mod_state || o_mod_state) {
        // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
        del_mods(mod_state);
        del_weak_mods(w_mod_state);
        del_oneshot_mods(o_mod_state);
        send_keyboard_report();
        tap_code16(code);
    } else {
        tap_code16(code);
    }
}

void tap_code_unset_mod(uint8_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    uint8_t w_mod_state;
    uint8_t o_mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state   = get_mods();
    w_mod_state = get_weak_mods();
    o_mod_state = get_oneshot_mods();
    if (mod_state || w_mod_state || o_mod_state) {
        // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
        del_mods(mod_state);
        del_weak_mods(w_mod_state);
        del_oneshot_mods(o_mod_state);
        send_keyboard_report();
        tap_code16(code);
    } else {
        tap_code(code);
    }
}

// Custom Shift Keys
const custom_shift_key_t custom_shift_keys[] = {
    //   {KC_COMMA, KC_SEMICOLON}, // Shift . is
    //   {KC_DOT, KC_COLON}, // Shift . is :
    //   {KC_8, KC_LEFT_PAREN}, // Shift 8 is (
    //   {KC_9, KC_RIGHT_PAREN}, // Shift 9 is )
    //   {KC_0, KC_ASTERISK}, // Shift 0 is *
    //   {KC_BACKSPACE, LALT(KC_BACKSPACE)}, // Shift Backspace is delete previous word
    //   {KC_DELETE, LALT(KC_DELETE)}, // Shift Delete is delete previous word
    {KC_BACKSPACE, KC_DELETE} // Shift Backspace is delete forward
    //   {KC_F6, KC_F16}, // Shift F-* is +10 F-*
    //   {KC_F7, KC_F17},
    //   {KC_F8, KC_F18},
    //   {KC_F9, KC_F19},
    //   {KC_F10, KC_F20},
    //   {KC_F11, KC_F21},
    //   {KC_F12, KC_F22},
    //   {KC_F13, KC_F23},
    //   {KC_F14, KC_F24},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Custom Gui Keys
// const custom_gui_key_t custom_gui_keys[] = {
//   {KC_DELETE, LCTL(KC_K)}, // Gui Delete is delete line forward
// };
// uint8_t NUM_CUSTOM_GUI_KEYS =
//     sizeof(custom_gui_keys) / sizeof(custom_gui_key_t);

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // ignore shift presses (ie. double quote)
        case KC_LSFT:
        case KC_RSFT:
            return true;
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            //   case KC_MINS: not sure why this is the default behaviour
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
            //   case KC_UNDS:
            //  Additional keycodes
        case KC_QUOT:
            return true;
        default:
            return false; // Deactivate Caps Word.
    }
}
// bool caps_sentence_press_user(uint16_t keycode) {
//     switch (keycode) {
//           // ignore shift presses (ie. double quote)
//         case KC_LSFT:
//         case KC_RSFT:
//             return true;

//         // Keycodes that continue Caps Word, with shift applied.
//         case KC_A ... KC_Z:
//             add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
//             return true;

//         // Keycodes that continue Caps Word, without shifting.
//         case KC_1 ... KC_0:
//         case KC_BSPACE:
//         case KC_DELETE:
//         case KC_MINUS:
//         case KC_UNDERSCORE:
//         //  Additional keycodes
//         case KC_QUOTE:
//         // case KC_DOUBLE_QUOTE:
//         case KC_GRAVE:
//         // caps sentence specific
//         // opening braces
//         case KC_LEFT_PAREN:
//         case KC_LBRACKET:
//         case KC_LEFT_CURLY_BRACE:
//         case KC_LEFT_ANGLE_BRACKET:
//         // punctuation
//         case KC_SPACE:
//         case KC_COMMA:
//             return true;

//         default:
//             return false;  // Deactivate Caps Word.
//     }
// }

/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_BACKSPACE) {
        if (record->event.pressed) {
            if (check_mods_sft_and_gui()) {
                tap_code16_no_mod(LCTL(KC_K)); // Gui shift backspace becomes delete line forward
                return false;                  // don't continue with custom shift keycodes below
            }
        } else {
            if (check_mods_sft_and_gui()) {
                // Since mods are re-applied after tap_code16_no_mod, we will need to cancel one shot mods if they are active.
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                    send_keyboard_report();
                }
            }
        }
    }
    // if (keycode == KC_DELETE) {
    //     if (record->event.pressed) {
    //       if (check_mods_gui) {
    //         tap_code16_no_mod(LCTL(KC_K));  // Gui delete becomes delete line forward
    //         return false;            // don't continue with custom shift keycodes below
    //       }
    //     } else {
    //         if (check_mods_gui()) {
    //            if (ONESHOT_MODS_ACTIVE) {
    //              clear_oneshot_mods();
    //              send_keyboard_report();
    //            }
    //         }
    //     }
    // }
    // only activate on base and qwerty layers
    // if (IS_LAYER_ON(BASE) || IS_LAYER_ON(QWRTY)) {
    //     if (!process_caps_word(keycode, record)) {
    //         return false;
    //     }
    // }
    // if (!process_caps_sentence(keycode, record, CAPS_SENTENCE)) { return false; }
    // don't activate on qwerty layer
    if (!IS_LAYER_ON(QWRTY)) {
        // if (!process_custom_gui_keys(keycode, record)) { return false; }
        if (!process_custom_shift_keys(keycode, record)) {
            return false;
        }
    }
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }
    if (!process_magic_shift(keycode, record)) {
        return false;
    }
    if (!process_cmd_tab_switcher(keycode, record)) {
        return false;
    }
    if (!process_oneshot_mods(keycode, record)) {
        return false;
    }
    if (!process_symbol_rolls(keycode, record, SYMBL)) {
        return false;
    }
    if (IS_LAYER_ON(BASE)) {
        if (!process_mash_arrows(keycode, record)) {
            return false;
        }
    }
    if (!process_mo_ext(keycode, record)) {
        return false;
    }
    // if (!hide_and_mute(keycode, record, KC_MUTE)) {
    //     return false;
    // }

    switch (keycode) {
        case TGL_LYT:
            if (record->event.pressed) {
                layer_off(HRDWR);
                if (IS_LAYER_ON(BASE)) {
                    // set_single_persistent_default_layer(QWRTY);
                    // dprint("BASE layer is on prior to switch");
                    layer_off(BASE);
                    layer_on(QWRTY);
                    default_layer_set(QWRTY);
                } else {
                    // set_single_persistent_default_layer(BASE);
                    // dprint("QWRTY layer is on prior to switch");
                    layer_off(QWRTY);
                    layer_on(BASE);
                    default_layer_set(BASE);
                }
            }
            return false;
            break;
        case LSFT(LGUI(KC_BSPC)):
            if (record->event.pressed) {
                tap_code16(LCTL(KC_K)); // Gui shift backspace becomes delete line forward
            }
            break;
        case OS_BSPC:
            if (record->event.pressed) {
                register_code(KC_BACKSPACE);
            } else {
                unregister_code(KC_BACKSPACE);
            }
            break;
        case OS_DEL:
            if (record->event.pressed) {
                register_code(KC_DELETE);
            } else {
                unregister_code(KC_DELETE);
            }
            break;
        case ENC_BTN:
            if (record->event.pressed) {
                // if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
                if (MODS_SFT) {
                    tap_code16_no_mod(OS_DRKMD_TGL);
                } else if (MODS_CTRL) {
                    tap_code16_no_mod(ZOOM_RESET);
                } else if (MODS_ALT) {
                    tap_code16_no_mod(ZOOM_RESET_APP);
                } else if (MODS_GUI) {
                    tap_code16(KC_H); // command-h
                } else {
                    tap_code(KC_MUTE);
                }
                return false;
            }
            break;
        case SHAKE_MOUSE:
            if (record->event.pressed) {
                register_code16(KC_MS_ACCEL1);
                int u;
                int i;
                int distance = 4;
                for (i = 1; i <= distance; ++i) {
                    tap_code(KC_MS_LEFT);
                }
                for (u = 1; u <= 6; ++u) {
                    for (i = 1; i <= distance; ++i) {
                        tap_code(KC_MS_RIGHT);
                        tap_code(KC_MS_UP);
                    }
                    for (i = 1; i <= distance; ++i) {
                        tap_code(KC_MS_RIGHT);
                        tap_code(KC_MS_DOWN);
                    }
                    for (i = 1; i <= distance; ++i) {
                        tap_code(KC_MS_LEFT);
                        tap_code(KC_MS_DOWN);
                    }
                    for (i = 1; i <= distance; ++i) {
                        tap_code(KC_MS_LEFT);
                        tap_code(KC_MS_UP);
                    }
                }
                for (i = 1; i <= distance; ++i) {
                    tap_code(KC_MS_RIGHT);
                }
                unregister_code16(KC_MS_ACCEL1);
            }
            break;
        case WNDW_LP_VRT_MAX:
            if (record->event.pressed) {
                // Key is being tapped.
                if (record->tap.count == 1) {
                    // Handle tap press event...
                    tap_code16(WNDW_ALMST_MAX);
                } else if (record->tap.count > 1) {
                    // Handle tap press event...
                    tap_code16(WNDW_VRT_MAX);
                // Key is being held.
                } else {
                    // Handle hold press event...
                    tap_code16(WNDW_VRT_MAX);
                }
            }
            return false; // Skip default handling.
            break;
        case WNDW_LP_ALMST_MAX:
            if (record->event.pressed) {
                if (record->tap.count > 0) { // Key is being tapped.
                    // Handle tap press event...
                    tap_code16(WNDW_LFT_HLF);
                } else { // Key is being held.
                    // Handle hold press event...
                    tap_code16(WNDW_MAX);
                }
            }
            return false; // Skip default handling.
            break;
        case WNDW_LP_SMLR:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(WNDW_SMLLR);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(WNDW_CNTR);
                }
            }
            return false; // Skip default handling.
            break;
        case WNDW_LP_LGR:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(WNDW_LRGR);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(WNDW_RSTR);
                }
            }
            return false; // Skip default handling.
            break;
        case WNDW_LP_LWP:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(WNDW_RGHT_HLF);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(WNDW_LWP);
                }
            }
            return false; // Skip default handling.
            break;
        case MSN_LP_FLLSCRN: // Mission Control on tap, OS full screen on long press
            // return process_tap_or_long_press_key(record, OS_FLLSCRN);
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(OS_MSN_CNTRL);
                } else {
                    // Handle tap release event...
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(OS_FLLSCRN);
                } else {
                    // Handle hold release event...
                }
            }
            return false; // Skip default handling.
            break;
        case PRV_SPC_LP:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(OS_PRV_SPC);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(OS_TL_WNDW_L);
                }
            }
            return false; // Skip default handling.
            break;
        case NXT_SPC_LP:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(OS_NXT_SPC);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(OS_TL_WNDW_R);
                }
            }
            return false; // Skip default handling.
            break;
        case QUOT_LP:
            return process_tap_or_long_press_key(record, KC_DOUBLE_QUOTE);
            break;
        case DOT_LP:
            return process_tap_or_long_press_key(record, KC_COMM);
            break;
        // Cancel Layer Lock on Escape
        case KC_ESC:
            if (record->event.pressed) {
                const uint8_t layer = get_highest_layer(layer_state);
                if (is_layer_locked(layer)) {
                    layer_lock_off(layer);
                    return false; // Skip default handling.
                }
            }
            break;
        case LT(MOUSE, KC_ESC):
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    const uint8_t layer = get_highest_layer(layer_state);
                    if (is_layer_locked(layer)) {
                        layer_lock_off(layer);
                        return false; // Skip default handling.
                    }
                }
            }
            break;
        // case LT(NUMNAV, KC_ESC):
        //     if (record->tap.count > 0) {
        //         if (record->event.pressed) {
        //             const uint8_t layer = get_highest_layer(layer_state);
        //             if (is_layer_locked(layer)) {
        //                 layer_lock_off(layer);
        //                 return false;  // Skip default handling.
        //             }
        //         }
        //     }
        //     break;
        case TGL_SELECT_LP:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // right once fixes toggle select on word/line beginnings
                    tap_code(KC_RIGHT);
                    tap_code16(LALT(KC_LEFT));
                    tap_code16(LALT(LSFT(KC_RGHT)));
                }
            } else {
                if (record->event.pressed) {
                    tap_code(KC_RIGHT);
                    tap_code16(LGUI(KC_LEFT));
                    tap_code16(LGUI(LSFT(KC_RGHT)));
                    // select all
                    // tap_code(KC_RIGHT);
                    // tap_code16(LGUI(KC_UP));
                    // tap_code16(LGUI(LSFT(KC_DOWN)));
                }
            }
            return false; // Skip default handling.
            break;
        // This was used with 3 button macro pad, bn003
        // case LP_TAB:
        //     if (record->tap.count > 0) {
        //         if (record->event.pressed) {
        //             tap_code16(LGUI(KC_T));
        //         }
        //     } else {
        //         if (record->event.pressed) {
        //             tap_code16(LGUI(KC_W));
        //         }
        //     }
        //     return false; // Skip default handling.
        //     break;
        case OS_LP_SCRN_SHT_FULL:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(OS_SCRN_SHT);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(OS_SCRN_SHT_CLP);
                }
            }
            return false;
            break;
        case OS_LP_SCRN_SHT_SLCT:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                    tap_code16(OS_SCRN_SHT_SLCT);
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                    tap_code16(OS_SCRN_SHT_CLP_SLCT);
                }
            }
            return false;
            break;
        // case OS_LP_SPTLGHT:
        //     if (record->tap.count > 0) { // Key is being tapped.
        //         if (record->event.pressed) {
        //             // Handle tap press event...
        //             tap_code16(OS_SPTLGHT);
        //         }
        //     } else { // Key is being held.
        //         if (record->event.pressed) {
        //             // Handle hold press event...
        //             tap_code16(OS_SPTLGHT_FNDR);
        //         }
        //     }
        //     return false;
        //     break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
#    if defined TECHNIK_KEYBOARD
void matrix_init_user(void) {
    g_led_config =
        (led_config_t){{{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33}, {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45}, {46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57}}, {{220, 17}, {172, 17}, {112, 17}, {50, 17}, {4, 17}, {4, 56}, {50, 56}, {112, 56}, {172, 56}, {220, 56}, {0, 0}, {20, 0}, {40, 0}, {61, 0}, {81, 0}, {101, 0}, {122, 0}, {142, 0}, {162, 0}, {183, 0}, {203, 0}, {224, 0}, {0, 21}, {20, 21}, {40, 21}, {61, 21}, {81, 21}, {101, 21}, {122, 21}, {142, 21}, {162, 21}, {183, 21}, {203, 21}, {224, 21}, {0, 42}, {20, 42}, {40, 42}, {61, 42}, {81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42}, {0, 64}, {20, 64}, {40, 64}, {61, 64}, {81, 64}, {101, 64}, {122, 64}, {142, 64}, {162, 64}, {183, 64}, {203, 64}, {224, 64}}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // Turn off bottom leds
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
        if (g_led_config.flags[i] == LED_FLAG_UNDERGLOW) {
            g_led_config.flags[i] = LED_FLAG_NONE;
        }
    }
}
#    endif
#endif

void keyboard_post_init_user(void) {
#ifdef QWERTY_BASE
    // Call the post init code.
    layer_off(BASE);
    layer_on(QWRTY);
    default_layer_set(QWRTY);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    cmd_tab_switcher_layer_state(state);
    oneshot_mods_layer_state(state);

    state = update_tri_layer_state(state, NUMNAV, SYMBL, OS);
    state = update_tri_layer_state(state, HRDWR, AUX, FUNC);

    // Use `static` variable to remember the previous status.
    static bool func_on = false;

    if (func_on != IS_LAYER_ON_STATE(state, FUNC)) {
        func_on = !func_on;
        if (func_on) {
// Just entered one of the FUNC layers.
#if defined EXECUTE_ON_FUNC
            register_code(KC_EXEC);
#endif
        } else {
// Just exited the one of FUNC layers.
#if defined EXECUTE_ON_FUNC
            unregister_code(KC_EXEC);
#endif
        }
    }

// always call cancel_key_lock()
#ifdef KEY_LOCK_ENABLE
    cancel_key_lock();
#endif

    return state;
}

void matrix_scan_user(void) {
    cmd_tab_switcher_matrix_scan_user();
}

#ifdef ENCODER_ENABLE
__attribute__((weak)) bool encoder_update_keymap(uint8_t index, bool clockwise) {
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            if (MODS_GUI) {
                // use cmd tab switcher so that is_command_tab_active() can be used with encoder and double tap to solely close apps when cmd tab is actually in use
                // tap_code16(LGUI(KC_TAB));
                cmd_tab_next();
                // } else if (MODS_SFT && !(IS_LAYER_ON(HRDWR)) && !(IS_LAYER_ON(AUX)) && !(IS_LAYER_ON(NUMPAD))) {
            } else if (MODS_SFT && !(IS_LAYER_ON(HRDWR)) && !(IS_LAYER_ON(AUX))) {
                tap_code16_no_mod(DISP_BRI);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_IN);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_IN_APP);
            } else if (IS_LAYER_ON(AUX)) {
                if (MODS_SFT) {
                    tap_code16_no_mod(REDO);
                } else {
                    tap_code16(OS_NXT_TAB);
                }
            } else if (IS_LAYER_ON(HRDWR)) {
                if (MODS_SFT) {
                    tap_code_no_mod(KC_RIGHT);
                } else {
                    tap_code(KC_DOWN);
                }
                // } else if (IS_LAYER_ON(NUMPAD)) {
                //     if (MODS_SFT) {
                //         tap_code(KC_WH_L);
                //     } else {
                //         tap_code(KC_WH_U);
                //     }
            } else {
                tap_code16(KC_VOLU);
            }
        } else {
            if (MODS_GUI) {
                // use cmd tab switcher so that is_command_tab_active() can be used with encoder and double tap to solely close apps when cmd tab is actually in use
                // tap_code16(LGUI(LSFT(KC_TAB)));
                cmd_tab_previous();
                // } else if (MODS_SFT && !(IS_LAYER_ON(HRDWR)) && !(IS_LAYER_ON(AUX)) && !(IS_LAYER_ON(NUMPAD))) {
            } else if (MODS_SFT && !(IS_LAYER_ON(HRDWR)) && !(IS_LAYER_ON(AUX))) {
                tap_code16_no_mod(DISP_DIM);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_OUT);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_OUT_APP);
            } else if (IS_LAYER_ON(AUX)) {
                if (MODS_SFT) {
                    tap_code16_no_mod(UNDO);
                } else {
                    tap_code16(OS_PRV_TAB);
                }
            } else if (IS_LAYER_ON(HRDWR)) {
                if (MODS_SFT) {
                    tap_code_no_mod(KC_LEFT);
                } else {
                    tap_code(KC_UP);
                }
                // } else if (IS_LAYER_ON(NUMPAD)) {
                //     if (MODS_SFT) {
                //         tap_code(KC_WH_R);
                //     } else {
                //         tap_code(KC_WH_D);
                //     }
            } else {
                tap_code16(KC_VOLD);
            }
        }
    }
    // abort retro tapping
    // retro_tapping_counter++;

    return false;
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT(MOUSE, KC_ESC):
            // return 350;
        // Increase Caps word accessibility
        case KC_LSFT:
            return 300;
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold per key (quickly use a layer hold)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):  // quickly use right shift
        case LT(HRDWR, KC_LEFT): // quickly use mods on arrow cluster
        case RGUI_T(KC_DOWN):
        case RALT_T(KC_UP):
        case RCTL_T(KC_RIGHT):
            return true;
        default:
            return false;
    }
}

// Mirror settings for get_permissive_hold()
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):  // quickly use right shift
        case LT(HRDWR, KC_LEFT): // quickly use mods on arrow cluster
        case RGUI_T(KC_DOWN):
        case RALT_T(KC_UP):
        case RCTL_T(KC_RIGHT):
            return true;
        default:
            return false;
    }
}

// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         // Might roll through arrow keys
//         case RGUI_T(KC_LEFT):
//         case RALT_T(KC_DOWN):
//         case RCTL_T(KC_UP):
//             return true;
//         default:
//             return false;
//     }
// }

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow per key spamming for arrow keys and escape
        case LT(HRDWR, KC_LEFT): // quickly use mods on arrow cluster
        case RGUI_T(KC_DOWN):
        case RALT_T(KC_UP):
        case RCTL_T(KC_RIGHT):
        case LT(MOUSE, KC_ESC):
            return QUICK_TAP_TERM - 20;
        // By default, remove the auto-repeat ability and activate the hold function instead.
        default:
            return 0;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // why not (but check firmware size in case this pushes that over)
        case LT(MOUSE, KC_ESC):
            return true;
        default:
            return false;
    }
}
