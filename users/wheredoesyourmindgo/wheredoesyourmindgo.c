#include "wheredoesyourmindgo.h"
#include "features/caps_word.h"
#include "features/caps_sentence.h"
#include "features/oneshot_mods.h"
#include "features/custom_shift_keys.h"
#include "features/custom_gui_keys.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"

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

void oopsy_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed && !state->interrupted && state->count == 1) {
        tap_code16(KC_APP);
    } else if (!state->pressed && !state->interrupted && state->count >= 2) {
        tap_code16(LGUI(KC_H));  // Hide Active Window
        // KC_MUTE will toggle on double tap which isn't ideal here
        int i;
        for (i = 1; i <= 20; ++i) {
            // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
            tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
        }
    } else {
        layer_on(LOWEST);
    }
}

void oopsy_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (IS_LAYER_ON(LOWEST)) {
        layer_off(LOWEST);
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
            if (MODS_RSFT) {
                tap_code16_no_mod(WNDW_ALMST_MAX);
            } else {
                tap_code16_no_mod(WNDW_CNTR);
            }
            break;
        case 2:
            tap_code16_no_mod(WNDW_RSTR);
            break;
    }
}

void multi_max_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (MODS_RSFT) {
                tap_code16_no_mod(WNDW_ALMST_MAX);
                tap_code16_no_mod(WNDW_VRT_MAX);
            } else {
                tap_code16_no_mod(WNDW_VRT_MAX);
            }
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
    [TD_OOPSY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oopsy_finished, oopsy_reset)
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
  {KC_DELETE, LALT(KC_DELETE)} // Shift Delete is delete previous word
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Custom Gui Keys
const custom_gui_key_t custom_gui_keys[] = {
  {KC_DELETE, LCTL(KC_K)}, // Gui Delete is delete line forward
};
uint8_t NUM_CUSTOM_GUI_KEYS =
    sizeof(custom_gui_keys) / sizeof(custom_gui_key_t);

/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_gui_keys(keycode, record)) { return false; }
    if (!process_custom_shift_keys(keycode, record)) { return false; }
    if (!process_caps_word(keycode, record)) { return false; }
    if (!process_caps_sentence(keycode, record, CAPS_SENTENCE)) { return false; }
    if (!process_magic_shift(keycode, record)) { return false; }
    if (!process_cmd_tab_switcher(keycode, record)) { return false; }
    if (!process_oneshot_mods(keycode, record)) { return false; }
    if (!process_symbol_rolls(keycode, record, LOW)) { return false; }

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
                #if defined MENU_ON_HIGHEST
                // Only on hold during LT(HIGHEST)
                if (!(record->tap.count > 0)) {
                    register_code(KC_MENU);
                }
                #endif
                // return true
            } else {
                #if defined MENU_ON_HIGHEST
                if (!(record->tap.count > 0)) {
                    unregister_code(KC_MENU);
                }
                #endif
                // Release layer hold if Highest_alt was toggled on during press
                if (IS_LAYER_ON(HIGHEST)) {
                    layer_off(HIGHEST);
                }
                if (IS_LAYER_ON(HIGHEST_ALT)) {
                    layer_off(HIGHEST_ALT);
                }
            }
            break;

        case TLNG_LFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(TLNG_LYT_BCK);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(TLNG_SHRNK);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(TLNG_DCR_MN_CT);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(TLNG_THRW_LFT);
                } else {
                    tap_code16(TLNG_MV_FCS_CCLK);
                }
            }
            break;
        case TLNG_ILFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(TLNG_LYT_INF);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(KC_NO);
                    // tap_code16_no_mod(WNDW_RSTR);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(TLNG_GLBL_TLNG);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(TLNG_RLD);
                } else {
                    tap_code16(TLNG_MV_FCS_MN);
                }
            }
            break;
        case TLNG_IRGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    // tap_code16_no_mod(TLNG_FSCRN);
                    tap_code16_no_mod(TLNG_FLT);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(TLNG_TGL_FLT_FCS);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(TLNG_MSE_FCS);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(TLNG_RVLT);
                } else {
                    tap_code16(TLNG_SWP_FCS_MN);
                }
            }
            break;
        case TLNG_RGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(TLNG_LYT_FWD);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(TLNG_EXP);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(TLNG_INCR_MN_CT);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(TLNG_THRW_RGHT);
                } else {
                    tap_code16(TLNG_MV_FCS_CLK);
                }
            }
            break;
        // case WNDW_LFT:
        //     if (record->event.pressed) {
        //         clear_oneshot_mods();
        //         if (MODS_LSFT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LGUI) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LALT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LCTRL) {
        //             tap_code16_no_mod(KC_NO);
        //         } else {
        //             tap_code16(OS_PRVS_APP_WNDW);
        //         }
        //     }
        //     break;
        // case WNDW_ILFT:
        //     if (record->event.pressed) {
        //         clear_oneshot_mods();
        //         if (MODS_LSFT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LGUI) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LALT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LCTRL) {
        //             tap_code16_no_mod(KC_NO);
        //         } else {
        //             tap_code16(WNDW_ALMST_MAX);
        //         }
        //     }
        //     break;
        // case WNDW_IRGHT:
        //     if (record->event.pressed) {
        //         clear_oneshot_mods();
        //         if (MODS_LSFT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LGUI) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LALT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LCTRL) {
        //             tap_code16_no_mod(KC_NO);
        //         } else {
        //             tap_code16(WNDW_VRT_MAX);
        //         }
        //     }
        //     break;
        // case WNDW_RGHT:
        //     if (record->event.pressed) {
        //         clear_oneshot_mods();
        //         if (MODS_LSFT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LGUI) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LALT) {
        //             tap_code16_no_mod(KC_NO);
        //         } else if (MODS_LCTRL) {
        //             tap_code16_no_mod(KC_NO);
        //         } else {
        //             tap_code16(OS_NXT_APP_WNDW);
        //         }
        //     }
        //     break;
        case TGL_LYT:
            if (record->event.pressed) {
                layer_off(HIGH);
                if (IS_LAYER_ON(BASE)) {
                    // dprint("BASE layer is on prior to switch");
                    layer_off(BASE);
                    layer_on(BASE_QWRTY);
                    default_layer_set(BASE_QWRTY);
                } else {
                    // dprint("BASE_QWRTY layer is on prior to switch");
                    layer_off(BASE_QWRTY);
                    layer_on(BASE);
                    default_layer_set(BASE);
                }
                return false;
            }
            break;
        case LT(HIGHEST_ALT, TGL_HIGHEST):
            if (record->event.pressed) {
                // Only on tap. See note below.
                if (record->tap.count > 0) {
                    if (IS_LAYER_ON(HIGHEST)) {
                        layer_off(HIGHEST);
                        layer_on(HIGHEST_ALT);
                    } else {
                        layer_off(HIGHEST_ALT);
                        layer_on(HIGHEST);
                    }
                    // returning false on tap prevents KC_APP from firing (not sure why)
                    return false;
                } else {
                    if (IS_LAYER_ON(HIGHEST)) {
                        layer_off(HIGHEST);
                        layer_on(HIGHEST_ALT);
                    }
                    return false;
                }
            } else {
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(HIGHEST_ALT)) {
                        layer_off(HIGHEST_ALT);
                        layer_on(HIGHEST);
                    }
                }
                return false;
            }
            break;
        // Everything in LT(HIGHEST/LOWEST has been done manually. Consider moving this to a tap dance function in the future.
        case LT(HIGHEST, TGL_HIGHEST):
            if (record->event.pressed) {
                // Only on tap. See note below.
                if (record->tap.count > 0) {
                    if (IS_LAYER_ON(HIGHEST)) {
                        layer_off(HIGHEST);
                        layer_on(HIGHEST_ALT);
                    } else {
                        layer_off(HIGHEST_ALT);
                        layer_on(HIGHEST);
                    }
                    // returning false on tap prevents KC_APP from firing (not sure why)
                    return false;
                } else {
                    if (IS_LAYER_ON(HIGHEST_ALT)) {
                        layer_off(HIGHEST_ALT);
                        layer_on(HIGHEST);
                    }
                    return false;
                }
            } else {
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(HIGHEST)) {
                        layer_off(HIGHEST);
                        layer_on(HIGHEST_ALT);
                    }
                }
                return false;
            }
            break;
        case LT(LOWER_ALT, TGL_LOWER):
            if (record->event.pressed) {
                // Only on tap. See note below.
                if (record->tap.count > 0) {
                    if (IS_LAYER_ON(LOWER)) {
                        layer_off(LOWER);
                        layer_on(LOWER_ALT);
                    } else {
                        layer_off(LOWER_ALT);
                        layer_on(LOWER);
                    }
                    // returning false on tap prevents KC_APP from firing (not sure why)
                    return false;
                } else {
                    if (IS_LAYER_ON(LOWER)) {
                        layer_off(LOWER);
                        layer_on(LOWER_ALT);
                    }
                    return false;
                }
            } else {
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(LOWER_ALT)) {
                        layer_off(LOWER_ALT);
                        layer_on(LOWER);
                    }
                }
                return false;
            }
            break;
        case LT(LOWER, TGL_LOWER):
            if (record->event.pressed) {
                // Only on tap. See note below.
                if (record->tap.count > 0) {
                    if (IS_LAYER_ON(LOWER)) {
                        layer_off(LOWER);
                        layer_on(LOWER_ALT);
                    } else {
                        layer_off(LOWER_ALT);
                        layer_on(LOWER);
                    }
                    // returning false on tap prevents KC_APP from firing (not sure why)
                    return false;
                } else {
                    if (IS_LAYER_ON(LOWER_ALT)) {
                        layer_off(LOWER_ALT);
                        layer_on(LOWER);
                    }
                    return false;
                }
            } else {
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(LOWER)) {
                        layer_off(LOWER);
                        layer_on(LOWER_ALT);
                    }
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
    layer_on(BASE_QWRTY);
    default_layer_set(BASE_QWRTY);
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
            if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
                tap_code16_no_mod(DISP_DIM);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_OUT);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_OUT_APP);
            } else {
                tap_code16(KC_VOLD);
            }
		} else {
            if (IS_LAYER_ON(HIGHER) ||  MODS_GUI) {
                tap_code16_no_mod(DISP_BRI);
            } else if (MODS_CTRL) {
                tap_code16_no_mod(ZOOM_IN);
            } else if (MODS_ALT) {
                tap_code16_no_mod(ZOOM_IN_APP);
            } else {
                tap_code16(KC_VOLU);
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
            return 225;
        case TD(TD_OOPSY):
        case TD(TD_MULTI_MAX):
        case TD(TD_MULTI_RSTR):
            return 300; // favor oopsy behavior
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ESC):
        case LT(LOW, KC_ENT):
        case LT(HIGH, KC_TAB):
        // case LT(HIGHER, KC_SPC):
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
        case LT(HIGH, KC_TAB):
        // case LT(HIGHER, KC_SPC):
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
//         case LT(HIGHER, KC_SPC):
//             return true;
//         default:
//             return false;
//     }
// }

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow per key spamming for arrow keys (return false, default behaviour)
        case RGUI_T(KC_LEFT):
        case RALT_T(KC_DOWN):
        case RCTL_T(KC_UP):
        case LT(HIGHEST, KC_RIGHT):
        case LT(HIGHEST, KC_SLSH):
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
        case LT(HIGH, KC_TAB):
        case LT(HIGHER, KC_SPC):
            return true;
        default:
            return false;
    }
} */
