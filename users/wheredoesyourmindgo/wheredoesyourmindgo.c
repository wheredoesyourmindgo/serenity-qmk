#include "wheredoesyourmindgo.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif


extern int retro_tapping_counter;

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


bool is_btn1_held = false;

bool is_cmd_tab_active = false;
bool is_cmd_tab_held = false;
uint16_t cmd_tab_timer = 0;
#define cmd_tab_timer_default_dur 1000;
#define cmd_tab_timer_fast_dur 600;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

bool caps_lock_active = false;
bool caps_word_active = false;
bool caps_sentence_active = false;

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

void cancel_quick_caps(void) {
    caps_sentence_active = false;
    caps_word_active = false;
    // only fire caps_lock if caps was active
    if (caps_lock_active) {
        caps_lock_active = false;
        // tap kc_capslock last, after everything is set false for custom macro
        // tap_code(KC_CAPSLOCK);
        tap_code_delay(KC_CAPS, CAPS_TAP_DELAY);
    }
}
void cancel_caps_word(void) {
    caps_word_active = false;
    // only fire caps_lock if caps was active
    if (caps_lock_active) {
        caps_lock_active = false;
        // tap kc_capslock last, after everything is set false for custom macro
        // tap_code(KC_CAPSLOCK);
        tap_code_delay(KC_CAPS, CAPS_TAP_DELAY);
    }
}

// void cancel_caps_sentence(void) {
//     caps_sentence_active = false;
//     if (caps_active) {
//         caps_active = false;
//         tap_code(KC_CAPSLOCK);
//     }
// }

// track last key pressed to determine if delete word should trigger
bool dontBspaceWord = false;

// Create an instance of 'td_tap_t' for the 'os_grave' tap dance.
// static td_tap_t os_grave_t = {.is_press_action = true, .state = TD_NONE};
// Create an instance of 'td_tap_t' for the 'lower_esc' tap dance.
// static td_tap_t lower_esc_t = {.is_press_action = true, .state = TD_NONE};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->interrupted) {
        return TD_INTERRUPTED;
    } else {
        return TD_NOT_INTERRUPTED;
    }
}

void lower_esc_finished(qk_tap_dance_state_t *state, void *user_data) {
    // lower_esc_t.state = cur_dance(state);

    /* In case shift is held down prior to Lower hold use Lower-alt layer. Without this block Lower must be held first, followed by a shift hold.
    if (MODS_LSFT) {
        layer_off(LOWER);
        layer_on(LOWER_ALT);
        // this is referring to actual left-shift key, not alternate shift
        unregister_mods(MOD_BIT(KC_LSFT));
    } else { */
    if (MODS_LCTRL || MODS_LALT || MODS_LGUI) {
        layer_off(LOWER);
        layer_on(BASE);
        alt_lshift_active = true;
        register_mods(MOD_BIT(KC_LSFT));
    } else {
        layer_on(LOWER);
    }
    // }
}
void lower_esc_reset(qk_tap_dance_state_t *state, void *user_data) {
    // lower_esc_t.state = cur_dance(state);
    if (MODS_LSFT && alt_lshift_active) {
        alt_lshift_active = false;
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    // Release layer hold if activated
    if (IS_LAYER_ON(LOWER)) {
        layer_off(LOWER);
    }
    // Release layer hold if Lower_alt was toggled on during press
    if (IS_LAYER_ON(LOWER_ALT)) {
        layer_off(LOWER_ALT);
    }
    if (!state->interrupted) {
        // Only fire escape if keypress was not interrupted AND special mode is not active AND left control, opt, and/or command is not being held
        // if (!ONESHOT_MODS_ACTIVE && !caps_sentence_active && !caps_word_active && !ONESHOT_LYR_ACTIVE) {
        if (!ONESHOT_MODS_ACTIVE && !caps_sentence_active && !caps_word_active && !MODS_LCTRL && !MODS_LALT && !MODS_LGUI) {
            tap_code(KC_ESC);
            return;
        }
        //  Cancel One Shot Mods (if active)
        if (ONESHOT_MODS_ACTIVE) {
            clear_oneshot_mods();
        }
        if (caps_sentence_active || caps_word_active) {
            cancel_quick_caps();
        }
    }
    // lower_esc_t.state = TD_NONE;
}

void low_ent_finished(qk_tap_dance_state_t *state, void *user_data) {
    // low_ent_t.state = cur_dance(state);
    layer_on(LOW);
}

void low_ent_reset(qk_tap_dance_state_t *state, void *user_data) {
    // low_ent_t.state = cur_dance(state);
    layer_off(LOW);
    if (!state->interrupted) {
        // Always fire enter
        tap_code(KC_ENT);
        if (caps_sentence_active || caps_word_active) {
            cancel_quick_caps();
        }
    }
    // low_ent_t.state = TD_NONE;
}

/*
void os_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
    // os_grave_t.state = cur_dance(state);
    layer_on(OS);
}
void os_grave_reset(qk_tap_dance_state_t *state, void *user_data) {
    // os_grave_t.state = cur_dance(state);
    // Don't turn off OS layer if cmd+tab is active. Instead, wait for timeout or base layer switch.
    if (!is_cmd_tab_active) {
        layer_off(OS);
    }
    if (!state->interrupted) {
        tap_code(KC_GRAVE);
    }
}
*/

void caps_word_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_mods(MOD_BIT(KC_LSFT));
    } else if (state->count == 2) {
        unregister_mods(MOD_BIT(KC_LSFT));
        if (!caps_lock_active && !caps_word_active && !caps_sentence_active) {
            caps_lock_active = true;
            caps_word_active = true;
            // Fixes kc_caps not activating w/ Planck. See https://docs.qmk.fm/#/feature_macros?id=tap_codeltkcgt.
            tap_code_delay(KC_CAPS, CAPS_TAP_DELAY);
        }
        // it's is unclear if reset_tap_dance() helps in this regard
        reset_tap_dance(state);
    }
}

void caps_word_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (MODS_LSFT) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
}

void caps_sentence_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_mods(MOD_BIT(KC_RSFT));
    } else if (state->count == 2) {
        unregister_mods(MOD_BIT(KC_RSFT));
        if (!caps_lock_active && !caps_sentence_active && !caps_word_active) {
            caps_lock_active = true;
            caps_sentence_active = true;
            // Fixes kc_caps not activating w/ Planck. See https://docs.qmk.fm/#/feature_macros?id=tap_codeltkcgt.
            tap_code_delay(KC_CAPS, CAPS_TAP_DELAY);
        }
        // it's is unclear if reset_tap_dance() helps in this regard
        reset_tap_dance(state);
    }
}

void caps_sentence_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (MODS_RSFT) {
        unregister_mods(MOD_BIT(KC_RSFT));
    }
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
        // register_mods(MOD_BIT(KC_LCTRL));
        layer_on(LOWEST);
    }
}

void oopsy_reset(qk_tap_dance_state_t *state, void *user_data) {
    // if (MODS_LCTRL) {
    if (IS_LAYER_ON(LOWEST)) {
        // unregister_mods(MOD_BIT(KC_LCTRL));
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
    [TD_LOWER_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lower_esc_finished, lower_esc_reset),
    [TD_LOW_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, low_ent_finished, low_ent_reset),
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(tgl_select, NULL, NULL),
    [TD_MULTI_MAX] = ACTION_TAP_DANCE_FN_ADVANCED(multi_max_each, NULL, NULL),
    [TD_MULTI_RSTR] = ACTION_TAP_DANCE_FN_ADVANCED(multi_rst_each, NULL, NULL),
    [TD_CAPS_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(caps_word_each, NULL, caps_word_reset),
    [TD_CAPS_SENTENCE] = ACTION_TAP_DANCE_FN_ADVANCED(caps_sentence_each, NULL, caps_sentence_reset),
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

    if (!(keycode == TRY_BSPACE_WORD)) {
        if (record->event.pressed) {
            dontBspaceWord = false;
        }
    }

    // This fixes issue where two shifted alphas occur (instead of one) after using sentence_end tap function
    // if (ONESHOT_MODS_ACTIVE & MOD_BIT(KC_LSFT) && record->event.pressed) {
    //     clear_oneshot_mods();
    // }
    switch (keycode) {
        case RSFT_T(KC_CAPS):
        case LSFT_T(KC_CAPS):
            if (record->event.pressed) {
                // Only when KC_CAPS
                if (record->tap.count > 0) {
                    if (caps_sentence_active || caps_word_active) {
                        cancel_quick_caps();
                        return false;
                    } else {
                        caps_lock_active = !caps_lock_active;
                    }
                }
            }
            break;
        case KC_CAPSLOCK:
            if (record->event.pressed) {
                if (caps_sentence_active || caps_word_active) {
                    cancel_quick_caps();
                    return false;
                } else {
                    caps_lock_active = !caps_lock_active;
                }
            }
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
        case DF(LOWEST):
        case DF(LOWER):
        case DF(LOW):
        case DF(HIGH):
        case DF(HIGHER):
        case DF(HIGHEST):
            // Cancel One Shot Mods (if active) is necessary when switching to layers other than base layer. This will prevent an issue where the keyboard might get stuck in a layer.
            if (record->event.pressed) {
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                }
            }
            break;
        case LT(OS, KC_ESC):
            if (record->event.pressed) {
                // Only on tap (ie. Not during LT(OS)
                if (record->tap.count > 0) {
                // Only fire escape special mode is not active
                if (!ONESHOT_MODS_ACTIVE && !caps_sentence_active && !caps_word_active) {
                    return true;
                }
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                }
                if (caps_sentence_active || caps_word_active) {
                    cancel_quick_caps();
                }
                return false;
                }
            }
            break;
        case KC_ESC:
            if (record->event.pressed) {
                // Only fire escape special mode is not active
                if (!ONESHOT_MODS_ACTIVE && !caps_sentence_active && !caps_word_active) {
                    return true;
                }
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                }
                if (caps_sentence_active || caps_word_active) {
                    cancel_quick_caps();
                }
                return false;
            }
            break;
        // See lower_esc tap dance reset function. That tap dance was setup because tap.count will always be 0 when a 0 value is used with Tapping Term.
        // case LT(LOWER, KC_ESC):
        //     if (record->event.pressed) {
        //         // Only when KC_ESC
        //         if (record->tap.count > 0) {
        //             // Cancel One Shot Mods (if active)
        //             if (ONESHOT_MODS_ACTIVE) {
        //                 clear_oneshot_mods();
        //             }
        //             if (caps_sentence_active || caps_word_active) {
        //                 cancel_quick_caps();
        //             }
        //         }
        //     }
        //     break;
        // Tab, space, colon, semi-colon, comma cancel caps word
        case KC_COLN:
        case KC_SCLN:
        case KC_COMM:
        // case KC_TAB: // see below
        case KC_SPC:
            if (record->event.pressed) {
                if (caps_word_active) {
                    cancel_caps_word();
                }
            }
            break;
        case LT(HIGH, KC_TAB):
            #if defined REMAP_PASTE
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL && !MODS_SFT)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL && !ONESHOT_MODS_SFT))
                ) {
                    tap_code(KC_D);
                    return false;
                } else {
                    // normal tab behavior
                    // Only on tap (ie. Not during LT(HIGH) and LT(HIGHER))
                    if (record->tap.count > 0) {
                        if (caps_word_active) {
                            cancel_caps_word();
                        }
                    }
                }
            }
            #else
            if (record->event.pressed) {
                // Only on tap (ie. Not during LT(HIGH) and LT(HIGHER))
                if (record->tap.count > 0) {
                    if (caps_word_active) {
                        cancel_caps_word();
                    }
                }
            }
            #endif
            break;
        case LT(HIGHER, KC_SPC):
        case LT(OS, KC_SPC):
            if (record->event.pressed) {
                if (MODS_RCTRL || MODS_RALT || MODS_RGUI) {
                    layer_on(BASE);
                    alt_rshift_active = true;
                    register_mods(MOD_BIT(KC_RSFT));
                    // abort retro tapping
                    retro_tapping_counter++;
                    return false;
                }
                // Only on tap (ie. Not during LT(OS) and LT(HIGHER))
                if (record->tap.count > 0) {
                    if (caps_word_active) {
                        cancel_caps_word();
                    }
                }
            } else {
                if (MODS_RSFT && alt_rshift_active) {
                    alt_rshift_active = false;
                    unregister_mods(MOD_BIT(KC_RSFT));
                }
            }
            break;
        // Enter, period (and escape) cancel caps word and caps sentence
        case KC_ENT:
            if (record->event.pressed) {
                if (caps_sentence_active || caps_word_active) {
                    cancel_quick_caps();
                }
                // We don't need to check if kc_dot was tapped in Lower layer cause once Lower is triggered via held dontBspaceWord will get reset. Same holds true for other keycodes used in and out of Lower layer (arrows, kc_del).
                dontBspaceWord = true;
                if (is_cmd_tab_active) {
                    cancel_cmd_shift();
                    return false;
                }
            }
            break;
        case KC_DOT:
            if (record->event.pressed) {
                if (caps_sentence_active || caps_word_active) {
                    cancel_quick_caps();
                }
                // We don't need to check if kc_dot was tapped in Lower layer cause once Lower is triggered via held dontBspaceWord will get reset. Same holds true for other keycodes used in and out of Lower layer (arrows, kc_del).
                dontBspaceWord = true;
            }
            break;
        // See low_ent tap dance reset function. That tap dance was setup because tap.count will always be 0 when a 0 value is used with Tapping Term.
        // case LT(LOW, KC_ENT):
        case ALGR_T(KC_DOT):
            if (record->event.pressed) {
                // Only on tap (ie. Not during LT(LOW) and alt)
                if (record->tap.count > 0) {
                    if (caps_sentence_active || caps_word_active) {
                        cancel_quick_caps();
                    }
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
        case VOL_JUP:
            if (record->event.pressed) {
                int i;
                for (i = 1; i <= 5; ++i) {
                    // tap_code(KC_VOLU) doesn't work w/ Planck
                    tap_code(KC__VOLUP);
                }
            }
            break;
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

        // Old layout, see TD_LOWER_ESC
        // case LT(LOWEST, KC_APP):
        //     if (record->event.pressed) {
        //         if (MODS_LCTRL || MODS_LALT || MODS_LGUI) {
        //             layer_on(BASE);
        //             register_mods(MOD_BIT(KC_LSFT));
        //             return false;
        //         }
        //     } else {
        //         if (MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //         }
        //     }
        //     break;

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
        // case WNDW_M_LFT:
        //     if (record->event.pressed) {
        //         // Fourth
        //         if (MODS_LCTRL) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             tap_code16(WNDW_FST_FRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //         // Third
        //         } else if (MODS_LALT) {
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             tap_code16(WNDW_LFT_THRD);
        //             register_mods(MOD_BIT(KC_LALT));
        //         // Half
        //         } else if (MODS_LGUI) {
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             tap_code16(WNDW_LFT_HLF);
        //             register_mods(MOD_BIT(KC_LGUI));
        //         // Two-thirds
        //         } else if (MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_LFT_TTHRD);
        //             register_mods(MOD_BIT(KC_LSFT));
        //         // Three-quarters
        //         } else if (MODS_LCTRL && MODS_LALT && MODS_LGUI && MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_FST_TFRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //             register_mods(MOD_BIT(KC_LALT));
        //             register_mods(MOD_BIT(KC_LGUI));
        //             register_mods(MOD_BIT(KC_LSFT));
        //         } else {
        //             tap_code16(WNDW_MV_LFT);
        //         }
        //     }
        //     break;
        // case WNDW_M_BTM:
        //      if (record->event.pressed) {
        //         // Fourth
        //         if (MODS_LCTRL && MODS_LALT && MODS_LGUI && MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_SCND_FRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //             register_mods(MOD_BIT(KC_LALT));
        //             register_mods(MOD_BIT(KC_LGUI));
        //             register_mods(MOD_BIT(KC_LSFT));
        //         // Third
        //         } else if (MODS_LCTRL) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             tap_code16(WNDW_CNTR_THRD);
        //             register_mods(MOD_BIT(KC_LCTL));
        //         // Half
        //         } else if (MODS_LALT) {
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             tap_code16(WNDW_BTTM_HLF);
        //             register_mods(MOD_BIT(KC_LALT));
        //         } else {
        //             tap_code16(WNDW_MV_LFT);
        //         }
        //     }
        // break;
        // case WNDW_M_TP:
        //      if (record->event.pressed) {
        //         // Fourth
        //         if (MODS_LCTRL && MODS_LALT && MODS_LGUI && MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_THRD_FRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //             register_mods(MOD_BIT(KC_LALT));
        //             register_mods(MOD_BIT(KC_LGUI));
        //             register_mods(MOD_BIT(KC_LSFT));
        //         // Third
        //         } else if (MODS_LCTRL) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             tap_code16(WNDW_CNTR_THRD);
        //             register_mods(MOD_BIT(KC_LCTL));
        //         // Half
        //         } else if (MODS_LALT) {
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             tap_code16(WNDW_TOP_HLF);
        //             register_mods(MOD_BIT(KC_LALT));
        //         } else {
        //             tap_code16(WNDW_MV_LFT);
        //         }
        //     }
        //     break;
        // case WNDW_M_RGHT:
        //     if (record->event.pressed) {
        //         // Fourth
        //         if (MODS_LCTRL) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             tap_code16(WNDW_FRTH_FRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //         // Third
        //         } else if (MODS_LALT) {
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             tap_code16(WNDW_RGNT_THRD);
        //             register_mods(MOD_BIT(KC_LALT));
        //         // Half
        //         } else if (MODS_LGUI) {
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             tap_code16(WNDW_RGHT_HLF);
        //             register_mods(MOD_BIT(KC_LGUI));
        //         // Two-thirds
        //         } else if (MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_RGHT_TTHRD);
        //             register_mods(MOD_BIT(KC_LSFT));
        //         // Three-quarters
        //         } else if (MODS_LCTRL && MODS_LALT && MODS_LGUI && MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_LST_TFRTH);
        //             register_mods(MOD_BIT(KC_LCTL));
        //             register_mods(MOD_BIT(KC_LALT));
        //             register_mods(MOD_BIT(KC_LGUI));
        //             register_mods(MOD_BIT(KC_LSFT));
        //         } else {
        //             tap_code16(WNDW_MV_LFT);
        //         }
        //     }
        //     break;
        // case WNDW_M_CNTR:
        //     if (record->event.pressed) {
        //         // Fourth
        //         if (MODS_LCTRL && MODS_LALT && MODS_LGUI && MODS_LSFT) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             unregister_mods(MOD_BIT(KC_LGUI));
        //             unregister_mods(MOD_BIT(KC_LSFT));
        //             tap_code16(WNDW_FST_FRTH);
        //             tap_code16(WNDW_CNTR);
        //             register_mods(MOD_BIT(KC_LCTL));
        //             register_mods(MOD_BIT(KC_LALT));
        //             register_mods(MOD_BIT(KC_LGUI));
        //             register_mods(MOD_BIT(KC_LSFT));
        //         // Third
        //         } else if (MODS_LCTRL) {
        //             unregister_mods(MOD_BIT(KC_LCTL));
        //             tap_code16(WNDW_CNTR_THRD);
        //             register_mods(MOD_BIT(KC_LCTL));
        //         // Half
        //         } else if (MODS_LALT) {
        //             unregister_mods(MOD_BIT(KC_LALT));
        //             tap_code16(WNDW_CNTR_HLF);
        //             register_mods(MOD_BIT(KC_LALT));
        //         } else {
        //             tap_code16(WNDW_CNTR);
        //         }
        //     }
        //     break;
        // case OS_MIN:
        //     if (record->event.pressed) {
        //         if (MODS_RSFT) {
        //             tap_code16_no_mod(WNDW_ALMST_MAX);
        //         } else {
        //             tap_code16(OS_MIN);
        //         }
        //         return false;
        //     }
        //     break;
        // case XWNDW_MAX:
        //     if (record->event.pressed) {
        //         if (MODS_RSFT) {
        //             tap_code16_no_mod(WNDW_ALMST_MAX);
        //             tap_code16_no_mod(WNDW_VRT_MAX);
        //             tap_code16_no_mod(WNDW_CNTR);
        //             register_mods(mod_state);
        //         } else {
        //             tap_code16(WNDW_MAX);
        //         }
        //         return false;
        //     }
        //     break;
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
        case BTN1_HOLD:
            if (record->event.pressed) {
                if (!is_btn1_held) {
                    register_code16(KC_BTN1);
                    is_btn1_held = true;
                } else {
                    unregister_code16(KC_BTN1);
                    is_btn1_held = false;
                }
            }
            break;
        case KC_D:
            #if defined REMAP_PASTE
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL && !MODS_SFT)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL && !ONESHOT_MODS_SFT))
                ) {
                    tap_code(KC_V);
                    return false;
                }
            }
            #endif
            break;
        case KC_V:
            #if defined REMAP_PASTE && !COLEMAK_DH_RING
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL && !MODS_SFT)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL && !ONESHOT_MODS_SFT))
                ) {
                    tap_code16(LSFT(KC_Z));
                    return false;
                }
            }
            #endif
            #if defined REMAP_PASTE && COLEMAK_DH_RING
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL))
                ) {
                    tap_code(KC_K);
                    return false;
                }
            }
            #endif
            break;
        case KC_K:
            #if defined REMAP_PASTE && COLEMAK_DH_RING
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL && !MODS_SFT)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL && !ONESHOT_MODS_SFT))
                ) {
                    tap_code16(LSFT(KC_Z));
                    return false;
                }
            }
            #endif
            break;
        case KC_TAB:
            #if defined REMAP_PASTE
            if (record->event.pressed) {
                if (
                    (MODS_GUI && (!MODS_ALT && !MODS_CTRL && !MODS_SFT)) ||
                    (ONESHOT_MODS_GUI && (!ONESHOT_MODS_LALT && !ONESHOT_MODS_CTRL && !ONESHOT_MODS_SFT))
                ) {
                    tap_code(KC_D);
                    return false;
                } else {
                    // normal tab behavior
                    if (caps_word_active) {
                        cancel_caps_word();
                    }
                }
            }
            #else
            if (record->event.pressed) {
                if (caps_word_active) {
                    cancel_caps_word();
                }
            }
            #endif
            break;
        case OS_LAST_SPC:
            if (record->event.pressed) {
                int i;
                for (i = 1; i <= 16; ++i) {
                    tap_code16(OS_NXT_SPC);
                }
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
            break;
        // default: //  for any other layers, or the default layer
        //     break;
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
    retro_tapping_counter++;
	return false;
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_TGL_SEL):
        case TD(TD_CAPS_WORD):
        case TD(TD_CAPS_SENTENCE):
            return TAPPING_TD_TERM;
        case TD(TD_OOPSY):
        case TD(TD_MULTI_MAX):
        case TD(TD_MULTI_RSTR):
            return 300; // favor oopsy behavior
        // case LT(HIGHEST, KC_LEFT):
        // case RGUI_T(KC_DOWN):
        // case RALT_T(KC_UP):
        // case RCTL_T(KC_RIGHT):
        //     return TAPPING_TD_FAST_TERM;
        // Using retro tapping with the following
        // case LT(LOW, KC_ENT):
        case TD(TD_LOW_ENT):
        // case LT(LOWER, KC_ESC):
        case TD(TD_LOWER_ESC):
        case LT(OS, KC_ESC):
        case LT(OS, KC_SPC):
            return 0;
        // While space key use retro tapping, we don't what to actiate the higher layer quickly with short tapping terms so just use default tapping term. We won't be rolling quickly through tab key so a shorter tapping term can be used with High layer.
        case LT(HIGHER, KC_SPC):
        case LT(HIGH, KC_TAB):
            return 225; // slightly longer
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT(LOW, KC_ENT):
        // case LT(LOWER, KC_ESC):
        // case LT(HIGH, KC_TAB):
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

/**
// We won't be rolling through all the Layer-tap keys
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT(LOWER, KC_ESC):
        // case LT(LOW, KC_ENT):
        case LT(HIGH, KC_TAB):
            return false;
        // Might roll through space
        // case LT(HIGHER, KC_SPC):
        default:
            return true;
    }
}
**/

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

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT(LOWER, KC_ESC):
        // case LT(LOW, KC_ENT):
        // case LT(LOWEST, KC_APP):
        case LT(HIGH, KC_TAB):
        case LT(HIGHER, KC_SPC):
        case LT(OS, KC_SPC):
        case LT(OS, KC_ESC):
            return true;
        default:
            return false;
    }
}
