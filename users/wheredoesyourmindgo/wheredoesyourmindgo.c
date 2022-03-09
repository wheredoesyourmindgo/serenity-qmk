#include "wheredoesyourmindgo.h"
#include "features/caps_word.h"
#include "features/caps_sentence.h"
#include "features/oneshot_mods.h"
#include "features/custom_shift_keys.h"
#include "features/custom_gui_keys.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"
#include "features/lyr_on_dual.h"
#include "features/layer_lock.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif


// extern int retro_tapping_counter;



void tap_code16_no_mod(uint16_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
    // del_mods(mod_state);
    unregister_mods(mod_state);
    tap_code16(code);
    // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
    // set_mods(mod_state);
    register_mods(mod_state);
}

void tap_code_no_mod(uint8_t code) {
    // Initialize variable holding the binary representation of active modifiers.
    uint8_t mod_state;
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
    // del_mods(mod_state);
    unregister_mods(mod_state);
    tap_code(code);
    // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
    // set_mods(mod_state);
    register_mods(mod_state);
}

// void oopsy_finished(qk_tap_dance_state_t *state, void *user_data) {
//     if (!state->pressed && !state->interrupted && state->count == 1) {
//         // KC_MUTE will toggle, instead, lower volume
//         int i;
//         for (i = 1; i <= 20; ++i) {
//             // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
//             tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
//         }
//     } else if (!state->pressed && !state->interrupted && state->count >= 2) {
//         // hide window first, then mute
//         tap_code16(LGUI(KC_H));  // Hide Active Window
//         // KC_MUTE will toggle, instead, lower volume
//         int i;
//         for (i = 1; i <= 20; ++i) {
//             // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
//             tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
//         }
//     } else {
//         layer_on(LOWEST);
//     }
// }


// void oopsy_reset(qk_tap_dance_state_t *state, void *user_data) {
//     if (IS_LAYER_ON(LOWEST) && !is_layer_locked(LOWEST)) {
//         layer_off(LOWEST);
//     }
// }

void oops_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
            tap_code16_no_mod(OS_DRKMD_TGL);
        } else if (MODS_CTRL) {
            tap_code16_no_mod(ZOOM_RESET);
        } else if (MODS_ALT) {
            tap_code16_no_mod(ZOOM_RESET_APP);
        } else {
            tap_code(KC_MUTE);
        }
    } else if (state->count == 2) {
        if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
            // nothing
        } else if (MODS_CTRL) {
            // nothing
        } else if (MODS_ALT) {
            // nothing
        } else {
            // hide window first, then mute
            tap_code16(LGUI(KC_H));  // Hide Active Window
            // KC_MUTE will toggle, instead, lower volume
            int i;
            for (i = 1; i <= 20; ++i) {
                // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
                tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
            }
        }
    }
}

void pemdas_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_ASTERISK);
            break;
        case 2:
            tap_code(KC_SLASH);
            break;
        case 3:
            tap_code16(KC_PLUS);
            break;
        case 4:
        case 5:
        case 6:
            tap_code(KC_MINUS);
            break;
    }
}

void tgl_select(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            // right once fixes toggle select on word/line beginnings
            tap_code(KC_RIGHT);
            tap_code16(LALT(KC_LEFT));
            tap_code16(LALT(LSFT(KC_RGHT)));
            break;
        case 2:
            tap_code(KC_RIGHT);
            tap_code16(LGUI(KC_LEFT));
            tap_code16(LGUI(LSFT(KC_RGHT)));
            break;
        case 3:
            tap_code(KC_RIGHT);
            tap_code16(LGUI(KC_UP));
            tap_code16(LGUI(LSFT(KC_DOWN)));
            reset_tap_dance(state);
            break;
    }
}

void multi_rst_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16_no_mod(WNDW_CNTR);
            break;
        case 2:
            tap_code16_no_mod(WNDW_RSTR);
            break;
    }
}

void multi_max_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16_no_mod(WNDW_VRT_MAX);
            break;
        case 2:
            tap_code16_no_mod(WNDW_MAX);
            break;
    }
}

// Tap once for Word Select, twice for Line Select, three times for all
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(tgl_select, NULL, NULL),
    [TD_MULTI_MAX] = ACTION_TAP_DANCE_FN_ADVANCED(multi_max_each, NULL, NULL),
    [TD_MULTI_RSTR] = ACTION_TAP_DANCE_FN_ADVANCED(multi_rst_each, NULL, NULL),
    // [TD_OOPSY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oopsy_finished, oopsy_reset),
    [TD_OOPS] = ACTION_TAP_DANCE_FN_ADVANCED(oops_each, NULL, NULL),
    [TD_PEMDAS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pemdas_finished, NULL),
};
// end of Tap Dance config


// Custom Shift Keys
const custom_shift_key_t custom_shift_keys[] = {
  {KC_COMMA, KC_SEMICOLON}, // Shift . is
  {KC_DOT, KC_COLON}, // Shift . is :
  {KC_8, KC_LEFT_PAREN}, // Shift 8 is (
  {KC_9, KC_RIGHT_PAREN}, // Shift 9 is )
  {KC_0, KC_ASTERISK}, // Shift 0 is *
  {KC_BACKSPACE, LALT(KC_BACKSPACE)}, // Shift Backspace is delete previous word
  {KC_DELETE, LALT(KC_DELETE)}, // Shift Delete is delete previous word
  {KC_F6, KC_F16}, // Shift F-* is +10 F-*
  {KC_F7, KC_F17},
  {KC_F8, KC_F18},
  {KC_F9, KC_F19},
  {KC_F10, KC_F20},
  {KC_F11, KC_F21},
  {KC_F12, KC_F22},
  {KC_F13, KC_F23},
  {KC_F14, KC_F24},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Custom Gui Keys
const custom_gui_key_t custom_gui_keys[] = {
  {KC_DELETE, LCTL(KC_K)}, // Gui Delete is delete line forward
};
uint8_t NUM_CUSTOM_GUI_KEYS =
    sizeof(custom_gui_keys) / sizeof(custom_gui_key_t);

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // ignore shift presses (ie. double quote)
        case KC_LSFT:
        case KC_RSFT:
            return true;

        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_MINS:
        case KC_UNDS:
        //  Additional keycodes
        case KC_QUOT:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
bool caps_sentence_press_user(uint16_t keycode) {
    switch (keycode) {
          // ignore shift presses (ie. double quote)
        case KC_LSFT:
        case KC_RSFT:
            return true;

        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_RSFT));  // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPACE:
        case KC_MINUS:
        case KC_UNDERSCORE:
        //  Additional keycodes
        case KC_QUOTE:
        // case KC_DOUBLE_QUOTE:
        case KC_GRAVE:
        // caps sentence specific
        // opening braces
        case KC_LEFT_PAREN:
        case KC_LBRACKET:
        case KC_LEFT_CURLY_BRACE:
        case KC_LEFT_ANGLE_BRACKET:
        // punctuation
        case KC_SPACE:
        case KC_COMMA:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}



/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // only activate on base and qwerty layers
    if (IS_LAYER_ON(BASE) || IS_LAYER_ON(QWRTY)) {
        if (!process_caps_word(keycode, record)) { return false; }
        if (!process_caps_sentence(keycode, record, CAPS_SENTENCE)) { return false; }
    }
    // don't activate on qwerty layer
    if (!IS_LAYER_ON(QWRTY)) {
        if (!process_custom_gui_keys(keycode, record)) { return false; }
        if (!process_custom_shift_keys(keycode, record)) { return false; }
    }
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
    if (!process_magic_shift(keycode, record)) { return false; }
    if (!process_cmd_tab_switcher(keycode, record)) { return false; }
    if (!process_oneshot_mods(keycode, record)) { return false; }
    if (!process_symbol_rolls(keycode, record, LOW)) { return false; }
    if (!process_layer_on_dual_hold(keycode, record)) { return false; }

    switch (keycode) {

        // case DISP_FDIM:
        //     if (record->event.pressed) {
        //         int i;
        //         for (i = 1; i <= 20; ++i) {
        //             tap_code(DISP_DIM);
        //         }
        //     }
        //     break;
        // case DISP_FBRI:
        //     if (record->event.pressed) {
        //         int i;
        //         for (i = 1; i <= 20; ++i) {
        //             tap_code(DISP_BRI);
        //         }
        //     }
        // Un-used, see TD_OOPSY
        // case OOPS:
        //     if (record->event.pressed) {
        //         tap_code16(LGUI(KC_H));  // Hide Active Window
        //         // KC_MUTE will toggle on double tap which isn't ideal here
        //         int i;
        //         for (i = 1; i <= 20; ++i) {
        //             // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
        //             tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
        //         }
        //     }
        //     break;

        case LT(HIGHEST, KC_RIGHT):
        case LT(HIGHEST, KC_SLSH):
            if (record->event.pressed) {
                #if defined EXECUTE_ON_HIGHEST
                // Only on hold during LT(HIGHEST)
                if (!(record->tap.count > 0)) {
                    register_code(KC_EXEC);
                }
                #endif
                // return true
            } else {
                #if defined EXECUTE_ON_HIGHEST
                if (!(record->tap.count > 0)) {
                    unregister_code(KC_EXEC);
                }
                #endif
            }
            break;
        case TLNG_LFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(WNDW_LFT_TTHRD);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(WNDW_LFT_HLF);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(WNDW_LFT_THRD);
                } else if (MODS_LCTRL) {
                    // tap_code16_no_mod(TLNG_THRW_LFT);
                } else {
                    tap_code16(WNDW_ALMST_MAX);
                }
            }
            break;
        case TLNG_ILFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(WNDW_SMLLR);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(WNDW_BTTM_HLF);
                } else if (MODS_LALT) {

                } else if (MODS_LCTRL) {
                    // tap_code16_no_mod(WNDW_RGNT_THRD);
                } else {
                    tap_code16(WNDW_CNTR_THRD);
                }
            }
            break;
        case TLNG_IRGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(WNDW_LRGR);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(WNDW_TOP_HLF);
                } else if (MODS_LALT) {
                    // tap_code16_no_mod(WNDW_TOP_HLF);
                } else if (MODS_LCTRL) {
                    // tap_code16_no_mod();
                } else {
                    tap_code16(WNDW_CNTR_HLF);
                }
            }
            break;
        case TLNG_RGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(WNDW_RGHT_TTHRD);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(WNDW_RGHT_HLF);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(WNDW_RGNT_THRD);
                } else if (MODS_LCTRL) {
                    // tap_code16_no_mod();
                } else {
                    tap_code16(WNDW_ALMST_MAX);
                    tap_code16(WNDW_VRT_MAX);
                }
            }
            break;
        case TGL_LYT:
            if (record->event.pressed) {
                layer_off(HIGH);
                if (IS_LAYER_ON(BASE)) {
                    // dprint("BASE layer is on prior to switch");
                    layer_off(BASE);
                    layer_on(QWRTY);
                    default_layer_set(QWRTY);
                } else {
                    // dprint("QWRTY layer is on prior to switch");
                    layer_off(QWRTY);
                    layer_on(BASE);
                    default_layer_set(BASE);
                }
                return false;
            }
            break;
        case ENC_BTN:
            if (record->event.pressed) {
                if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
                    tap_code16_no_mod(OS_DRKMD_TGL);
                } else if (MODS_CTRL) {
                    tap_code16_no_mod(ZOOM_RESET);
                } else if (MODS_ALT) {
                    tap_code16_no_mod(ZOOM_RESET_APP);
                } else {
                    tap_code(KC_MUTE);
                }
                return false;
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
        case OS_BCK_FWD:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_SFT) {
                    tap_code16_no_mod(LGUI(KC_RIGHT_BRACKET));
                } else {
                    tap_code16(LGUI(KC_LEFT_BRACKET));
                }
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
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
#if defined TECHNIK_KEYBOARD
    void matrix_init_user(void) {
        g_led_config = (led_config_t){ {
            { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
            { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
            { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
            { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57}
        }, {
            {220, 17}, {172, 17}, {112, 17}, { 50, 17}, {  4, 17}, {  4, 56}, { 50, 56}, {112, 56}, {172, 56}, {220, 56},
            {  0,  0}, { 20,  0}, { 40,  0}, { 61,  0}, { 81,  0}, {101,  0}, {122,  0}, {142,  0}, {162,  0}, {183,  0}, {203,  0}, {224,  0},
            {  0, 21}, { 20, 21}, { 40, 21}, { 61, 21}, { 81, 21}, {101, 21}, {122, 21}, {142, 21}, {162, 21}, {183, 21}, {203, 21}, {224, 21},
            {  0, 42}, { 20, 42}, { 40, 42}, { 61, 42}, { 81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42},
            {  0, 64}, { 20, 64}, { 40, 64}, { 61, 64}, { 81, 64}, {101, 64}, {122, 64}, {142, 64}, {162, 64}, {183, 64}, {203, 64}, {224, 64}
        }, {
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
            1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
            1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        } };
        // Turn off bottom leds
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
            if (g_led_config.flags[i] == LED_FLAG_UNDERGLOW) {
                g_led_config.flags[i] = LED_FLAG_NONE;
            }
        }
    }
#endif
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

    switch (get_highest_layer(state)) {
        // case BASE:
        //     break;
        default: //  for any other layers, or the default layer
#ifdef KEY_LOCK_ENABLE
            cancel_key_lock();
#endif
            break;
    }

    return state;
}


void matrix_scan_user(void) {
  cmd_tab_switcher_matrix_scan_user();
}


#ifdef ENCODER_ENABLE
__attribute__((weak)) bool encoder_update_keymap(uint8_t index, bool clockwise) { return true; }

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) { return false; }
	if(index == 0) {
		if (clockwise) {
            if (IS_LAYER_ON(HIGHER) ||  MODS_GUI) {
                tap_code16_no_mod(DISP_BRI);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_IN);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_IN_APP);
            } else {
                tap_code16(KC_VOLU);
            }
		} else {
            if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
                tap_code16_no_mod(DISP_DIM);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_OUT);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_OUT_APP);
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
        case TD(TD_TGL_SEL):
        // case TD(TD_OOPSY):
            return 225;
        case TD(TD_MULTI_MAX):
        case TD(TD_MULTI_RSTR):
        case TD(TD_PEMDAS):
        case TD(TD_OOPS):
            return 300;
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold per key (quickly use a layer hold)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ESC):
        case LT(LOW, KC_ENT):
        // case LT(HIGHER, KC_TAB):
        // case LT(HIGH, KC_SPC):
        case RGUI_T(KC_LEFT):
        case RALT_T(KC_DOWN):
        case RCTL_T(KC_UP):
        case LT(HIGHEST, KC_RIGHT):
        case LT(HIGHEST, KC_SLSH):
            return true;
        default:
            return false;
    }
}

// Mirror settings for get_permissive_hold()
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ESC):
        case LT(LOW, KC_ENT):
        // case LT(HIGHER, KC_TAB):
        // case LT(HIGH, KC_SPC):
        case RGUI_T(KC_LEFT):
        case RALT_T(KC_DOWN):
        case RCTL_T(KC_UP):
        case LT(HIGHEST, KC_RIGHT):
        case LT(HIGHEST, KC_SLSH):
            return true;
        default:
            return false;
    }
}

// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         // Might roll through space
//         case LT(HIGH, KC_SPC):
//             return true;
//         default:
//             return false;
//     }
// }

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow per key spamming for arrow keys (return false, default behaviour) and grave/tilde
        case RGUI_T(KC_LEFT):
        case RALT_T(KC_DOWN):
        case RCTL_T(KC_UP):
        case LT(HIGHEST, KC_RIGHT):
        case LT(HIGHEST, KC_SLSH):
        case LT(LOWEST, KC_GRAVE):
        case LT(LOWEST, KC_MINS):
            return false;
        // Force hold by default
        default:
            return true;
    }
}

/* bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ESC):
        case LT(LOW, KC_ENT):
        // case LT(LOWEST, KC_APP):
        case LT(HIGHER, KC_TAB):
        case LT(HIGH, KC_SPC):
            return true;
        default:
            return false;
    }
} */
