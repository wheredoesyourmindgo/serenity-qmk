#include "wheredoesyourmindgo.h"
#include "features/caps_word.h"
#include "features/caps_sentence.h"
#include "features/oneshot_mods.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif


// extern int retro_tapping_counter;

#define MODS_RSFT (get_mods() & MOD_BIT(KC_RSFT))
#define MODS_LSFT (get_mods() & MOD_BIT(KC_LSFT))
#define MODS_RCTRL (get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_LCTRL (get_mods() & MOD_BIT(KC_LCTRL))
#define MODS_RALT (get_mods() & MOD_BIT(KC_RALT))
#define MODS_LALT (get_mods() & MOD_BIT(KC_LALT))
#define MODS_RGUI (get_mods() & MOD_BIT(KC_RGUI))
#define MODS_LGUI (get_mods() & MOD_BIT(KC_LGUI))
#define MODS_SFT (MODS_LSFT || MODS_RSFT)
#define MODS_CTRL (MODS_LCTRL || MODS_RCTRL)
#define MODS_ALT (MODS_LALT || MODS_RALT)
#define MODS_GUI (MODS_LGUI || MODS_RGUI)
// #define ACTIVE_MODS (get_mods())
// #define ONESHOT_LYR_ACTIVE (is_oneshot_layer_active())
#define ONESHOT_MODS_ACTIVE (get_oneshot_mods())
#define ONESHOT_MODS_LSFT (get_oneshot_mods() & MOD_BIT(KC_LSFT))
#define ONESHOT_MODS_LGUI (get_oneshot_mods() & MOD_BIT(KC_LGUI))
#define ONESHOT_MODS_RGUI (get_oneshot_mods() & MOD_BIT(KC_RGUI))
#define ONESHOT_MODS_LALT (get_oneshot_mods() & MOD_BIT(KC_LALT))
#define ONESHOT_MODS_LCTL (get_oneshot_mods() & MOD_BIT(KC_LCTL))
#define ONESHOT_MODS_RSFT (get_oneshot_mods() & MOD_BIT(KC_RSFT))
#define ONESHOT_MODS_RALT (get_oneshot_mods() & MOD_BIT(KC_RALT))
#define ONESHOT_MODS_RCTL (get_oneshot_mods() & MOD_BIT(KC_RCTL))
#define ONESHOT_MODS_GUI (ONESHOT_MODS_LGUI || ONESHOT_MODS_RGUI)
#define ONESHOT_MODS_ALT (ONESHOT_MODS_LALT || ONESHOT_MODS_RALT)
#define ONESHOT_MODS_CTRL (ONESHOT_MODS_LCTL || ONESHOT_MODS_RCTL)
#define ONESHOT_MODS_SFT (ONESHOT_MODS_LSFT || ONESHOT_MODS_RSFT)


bool is_cmd_tab_active = false;
bool is_cmd_tab_held = false;
uint16_t cmd_tab_timer = 0;
#define cmd_tab_timer_default_dur 1000;
#define cmd_tab_timer_fast_dur 600;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

// Track whether alt-shift is being used so that we don't get stuck in lower/higher layers when using dedicated shift keys with mods
bool alt_lshift_active = false;
bool alt_rshift_active = false;

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


// track last key pressed to determine if delete word should trigger
bool dontBspaceWord = false;



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

void cancel_cmd_shift(void) {
    unregister_mods(MOD_BIT(KC_LGUI));
    if (MODS_LSFT) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    is_cmd_tab_active = false;
    cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
}

/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    if (!process_caps_sentence(keycode, record)) { return false; }
    process_oneshot_mods(keycode, record);

    if (!(keycode == TRY_BSPACE_WORD)) {
        if (record->event.pressed) {
            dontBspaceWord = false;
        }
    }

    switch (keycode) {
        case OS_PRV_SPC:
        case OS_NXT_SPC:
            if (record->event.pressed) {
                is_cmd_tab_held = true;
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
            }
            break;
        case CMD_TAB_NXT:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_mods(MOD_BIT(KC_LGUI));
                } else {
                    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
                    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
                }
                is_cmd_tab_held = true;
                unregister_mods(MOD_BIT(KC_LSFT));
                // cmd_tab_timer = timer_read(); // Start the timer when the key is released, not pressed
                tap_code(KC_TAB);
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
                // unregister_code(KC_TAB);
            }
            break;
        // case CMD_TAB_HIDE:
        //     if (record->event.pressed) {
        //         if (is_cmd_tab_active) {
        //             cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
        //             cmd_tab_timer = timer_read();
        //             tap_code(KC_H);
        //             return false;
        //         }
        //     }
        //     break;
        case OS_EXPOSE:
            if (record->event.pressed) {
                if (is_cmd_tab_active) {
                    tap_code(KC_UP);
                    return false;
                }
            }
            break;
        case OS_DOCK:
            if (record->event.pressed) {
                // Hide app during cmd+tab
                if (is_cmd_tab_active) {
                    cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
                    cmd_tab_timer = timer_read();
                    tap_code(KC_H);
                    return false;
                }
            }
            break;
        case CMD_TAB_PRV:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                } else {
                    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
                    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
                }
                register_mods(MOD_BIT(KC_LSFT));
                tap_code(KC_TAB);
                is_cmd_tab_held = true;
                // cmd_tab_timer = timer_read();
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
                unregister_mods(MOD_BIT(KC_LSFT));
                // unregister_code(KC_TAB);
            }
            break;
        case DF(BASE):
            // Waiting for release will prevent key from firing. eg. prevent extra Enter keypress when using Enter to return to Base layer
            if (!record->event.pressed) {
                // Immediately end cmd+tab when base layer is set
                if (is_cmd_tab_active) {
                    cancel_cmd_shift();
                }
            }
            break;
        case KC_ESC:
            if (record->event.pressed) {
                // Only fire escape special mode is not active
                if (!ONESHOT_MODS_ACTIVE) {
                    return true;
                }
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                }
                return false;
            }
            break;
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
        // Enter, period (and escape) cancel caps word and caps sentence
        case KC_ENT:
            if (record->event.pressed) {
                // We don't need to check if kc_dot was tapped in Lower layer cause once Lower is triggered via held dontBspaceWord will get reset. Same holds true for other keycodes used in and out of Lower layer (arrows, kc_del).
                dontBspaceWord = true;
                if (is_cmd_tab_active) {
                    cancel_cmd_shift();
                    return false;
                }
            }
            break;
        case DISP_FDIM:
            if (record->event.pressed) {
                int i;
                for (i = 1; i <= 20; ++i) {
                    tap_code(DISP_DIM);
                }
            }
            break;
        case DISP_FBRI:
            if (record->event.pressed) {
                int i;
                for (i = 1; i <= 20; ++i) {
                    tap_code(DISP_BRI);
                }
            }
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
        // We don't need to check if kc_del was tapped in Lower layer cause once Lower is triggered via held dontBspaceWord will get reset. Same holds true for other keycodes used in and out of Lower layer (arrows, kc_dot).
        case KC_1 ... KC_0:
        case KC_RIGHT ... KC_UP:
        case KC_DEL:
            if (record->event.pressed) {
                dontBspaceWord = true;
            }
            break;
        case TRY_BSPACE_WORD:
            if (record->event.pressed) {
                if (dontBspaceWord) {
                    tap_code(KC_BSPACE);
                } else {
                    tap_code16(BSPC_PRV_WRD);
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
        case WNDW_LFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(VOID);
                } else {
                    tap_code16(OS_PRVS_APP_WNDW);
                }
            }
            break;
        case WNDW_ILFT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(VOID);
                } else {
                    tap_code16(WNDW_ALMST_MAX);
                }
            }
            break;
        case WNDW_IRGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(VOID);
                } else {
                    tap_code16(WNDW_VRT_MAX);
                }
            }
            break;
        case WNDW_RGHT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                if (MODS_LSFT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LGUI) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LALT) {
                    tap_code16_no_mod(VOID);
                } else if (MODS_LCTRL) {
                    tap_code16_no_mod(VOID);
                } else {
                    tap_code16(OS_NXT_APP_WNDW);
                }
            }
            break;
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
        case KC_DOT:
            if (record->event.pressed) {
                // We don't need to check if kc_dot was tapped in Lower layer cause once Lower is triggered via held dontBspaceWord will get reset. Same holds true for other keycodes used in and out of Lower layer (arrows, kc_del).
                dontBspaceWord = true;
                if (IS_LAYER_ON(BASE) && MODS_SFT && !MODS_ALT && !MODS_CTRL && !MODS_GUI) {
                    tap_code16(KC_COLN);
                    return false;
                }
            }
            break;
        case KC_COMM:
            if (record->event.pressed) {
                if (IS_LAYER_ON(BASE) && MODS_SFT && !MODS_ALT && !MODS_CTRL && !MODS_GUI) {
                    tap_code_no_mod(KC_SCOLON);
                    return false;
                }
            }
            break;
        case KC_LT:
        case KC_GT:
        case KC_LCBR:
        case KC_RCBR:
        case KC_LBRC:
        case KC_RBRC:
            if (record->event.pressed) {
                tap_code16(keycode);
                // immediately un-register mods (don't wait for keypress release)
                uint8_t mod_state;
                mod_state = get_mods();
                unregister_mods(mod_state);
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
    switch (get_highest_layer(state)) {
        case BASE:
            if (is_cmd_tab_active) {
                // cancel app swithing when switching back to base layer
                cancel_cmd_shift();
            }
            cancel_key_lock();
            break;
        default: //  for any other layers, or the default layer
            cancel_key_lock();
            // Cancel One Shot Mods (if active) is necessary when switching to layers other than base layer. This will prevent an issue where the keyboard might get stuck in a layer.
            if (ONESHOT_MODS_ACTIVE) {
                clear_oneshot_mods();
            }
            break;
    }
  return state;
}


// LEADER_EXTERNS();

void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > cmd_tab_timer_timeout && !is_cmd_tab_held) {
            cancel_cmd_shift();
        }
    }
}

    // Leaders
    //    LEADER_DICTIONARY() {
    //     leading = false;
    //     leader_end();

    //     SEQ_ONE_KEY(KC_L) {
    //       // Alfred
    //       tap_code16(LALT(KC_SPC));
    //     }
    //     SEQ_ONE_KEY(KC_T) {
    //       // iTerm
    //       tap_code16(LCTL(KC_SPC));
    //     }
    //     SEQ_TWO_KEYS(KC_Y, KC_D) {
    //       SEND_STRING("yarn dev");
    //     }
    //     SEQ_TWO_KEYS(KC_Y, KC_I) {
    //       SEND_STRING("yarn install");
    //     }
    //     SEQ_TWO_KEYS(KC_G, KC_P) {
    //       SEND_STRING("git pull");
    //     }
    //   }
// }
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
