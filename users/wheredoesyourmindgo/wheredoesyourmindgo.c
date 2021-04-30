#include "wheredoesyourmindgo.h"

#ifdef CONSOLE_ENABLE
    #include "print.h"
#endif

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Functions associated with individual tap dances
void caps_word_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_word_reset(qk_tap_dance_state_t *state, void *user_data);
void caps_sentence_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_sentence_reset(qk_tap_dance_state_t *state, void *user_data);


bool caps_active = false;
bool caps_word_active = false;
bool caps_sentence_active = false;
void caps_word_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed && !state->interrupted && state->count >= 2) {
        if (!caps_active && !caps_word_active && !caps_sentence_active) {
            caps_active = true;
            caps_word_active = true;
            tap_code(KC_CAPSLOCK);
        }
    } else {
        register_mods(MOD_BIT(KC_LSFT));
    }
}

void caps_word_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed && !state->interrupted && state->count >= 2) {
        // return
    } else {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
}


void caps_sentence_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed && !state->interrupted && state->count >= 2) {
        if (!caps_active && !caps_sentence_active && !caps_word_active) {
            caps_active = true;
            caps_sentence_active = true;
            tap_code(KC_CAPSLOCK);
        }
    } else {
        register_mods(MOD_BIT(KC_RSFT));
    }
}

void caps_sentence_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed && !state->interrupted && state->count >= 2) {
        // return
    } else {
        unregister_mods(MOD_BIT(KC_RSFT));
    }
}

void tgl_select(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(LALT(KC_LEFT));
            tap_code16(LALT(LSFT(KC_RGHT)));
            break;
        case 2:
            tap_code16(LGUI(KC_LEFT));
            tap_code16(LGUI(LSFT(KC_RGHT)));
            break;
        case 3:
        case 4:
            tap_code16(LGUI(KC_UP));
            tap_code16(LGUI(LSFT(KC_DOWN)));
            break;
    }
}


// Tap once for Word Select, twice for Line Select, three times for all
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(tgl_select, NULL, NULL),
    [TD_CAPS_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_word_finished, caps_word_reset),
    [TD_CAPS_SENTENCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_sentence_finished, caps_sentence_reset),
};
// end of Tap Dance config

/* Macros */
bool is_cmd_tab_active = false;
bool is_cmd_tab_held = false;
uint16_t cmd_tab_timer = 0;
#define cmd_tab_timer_default_dur 1000;
#define cmd_tab_timer_fast_dur 600;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

// #define MODS_SFT (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_RSFT (get_mods() & MOD_BIT(KC_RSFT))
#define MODS_LSFT (get_mods() & MOD_BIT(KC_LSFT))
// #define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_RCTRL (get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_LCTRL (get_mods() & MOD_BIT(KC_LCTRL))
// #define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))
#define MODS_RALT (get_mods() & MOD_BIT(KC_RALT))
#define MODS_LALT (get_mods() & MOD_BIT(KC_LALT))
// #define MODS_GUI (get_mods() & MOD_BIT(KC_LGUI) || get_mods() & MOD_BIT(KC_RGUI))
#define MODS_RGUI (get_mods() & MOD_BIT(KC_RGUI))
#define MODS_LGUI (get_mods() & MOD_BIT(KC_LGUI))
// #define ACTIVE_MODS (get_mods())
#define ONESHOT_LYR_ACTIVE (is_oneshot_layer_active())
#define ONESHOT_MODS_ACTIVE (get_oneshot_mods())
#define ONESHOT_MODS_LSFT (get_oneshot_mods() & MOD_BIT(KC_LSFT))
#define ONESHOT_MODS_LGUI (get_oneshot_mods() & MOD_BIT(KC_LGUI))
#define ONESHOT_MODS_LALT (get_oneshot_mods() & MOD_BIT(KC_LALT))
#define ONESHOT_MODS_LCTL (get_oneshot_mods() & MOD_BIT(KC_LCTL))
#define ONESHOT_MODS_RSFT (get_oneshot_mods() & MOD_BIT(KC_RSFT))
#define ONESHOT_MODS_RGUI (get_oneshot_mods() & MOD_BIT(KC_RGUI))
#define ONESHOT_MODS_RALT (get_oneshot_mods() & MOD_BIT(KC_RALT))
#define ONESHOT_MODS_RCTL (get_oneshot_mods() & MOD_BIT(KC_RCTL))

void cancel_quick_caps(void) {
   if (caps_sentence_active || caps_word_active) {
        caps_active = false;
        caps_sentence_active = false;
        caps_word_active = false;
        tap_code(KC_CAPSLOCK);
    }
}

void cancel_caps_word(void) {
   if (caps_word_active) {
        caps_active = false;
        caps_word_active = false;
        tap_code(KC_CAPSLOCK);
    }
}

void cancel_caps_sentence(void) {
   if (caps_sentence_active) {
        caps_active = false;
        caps_sentence_active = false;
        tap_code(KC_CAPSLOCK);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (ONESHOT_LYR_ACTIVE && IS_LAYER_ON(BASE_HRM) && !record->event.pressed) {
        switch (keycode) {
            case KC_ESC:
            case LT(OS,KC_ESC):
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    }
    // This fixes issue where two shifted alphas occur (instead of one) after using sentence_end tap function
    // if (ONESHOT_MODS_ACTIVE & MOD_BIT(KC_LSFT) && record->event.pressed) {
    //     clear_oneshot_mods();
    // }
    switch (keycode) {
        case KC_CAPSLOCK:
            if (record->event.pressed) {
                if ((caps_sentence_active || caps_word_active) && caps_active) {
                    cancel_quick_caps();
                } else {
                    if (caps_active) {
                        caps_active = false;
                        tap_code(KC_CAPSLOCK);
                    } else {
                        caps_active = true;
                        tap_code(KC_CAPSLOCK);
                    }
               }
            }
            return false;
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
        case PRV_APP:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_TAB));
            }
            break;
        case OS_PRV_SPC:
        case OS_NXT_SPC:
            if (record->event.pressed) {
                is_cmd_tab_held = true;
            } else {
                cmd_tab_timer = timer_read();
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
                // cmd_tab_timer = timer_read(); // Start the timer when the key is released, not pressed
                register_code(KC_TAB);
            } else {
                cmd_tab_timer = timer_read();
                is_cmd_tab_held = false;
                unregister_code(KC_TAB);
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
                register_code(KC_TAB);
                is_cmd_tab_held = true;
                // cmd_tab_timer = timer_read();
            } else {
                cmd_tab_timer = timer_read();
                is_cmd_tab_held = false;
                unregister_mods(MOD_BIT(KC_LSFT));
                unregister_code(KC_TAB);
            }
            break;
        case KC_ESC:
        case LT(OS,KC_ESC):
            if (record->event.pressed) {
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                }
                cancel_quick_caps();
            } else {
                // Immediately end cmd+tab when OS Layer-tap is released
                if (is_cmd_tab_active) {
                    unregister_mods(MOD_BIT(KC_LGUI));
                    is_cmd_tab_active = false;
                    cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
                }
            }
            break;
        // Tab, space, colon, semi-colon, comma cancel caps word
        case KC_TAB:
        case KC_SPC:
        case LT(LOW,KC_SPC):
        case KC_COLN:
        case KC_SCLN:
        case KC_COMM:
            if (record->event.pressed) {
                cancel_caps_word();
            }
            break;
        // Enter, period (and escape) cancel caps word and caps sentence
        case KC_ENT:
        case LT(HIGH,KC_ENT):
        case KC_DOT:
        case ALGR_T(KC_DOT):
            if (record->event.pressed) {
                cancel_quick_caps();
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
            break;
        case VOL_JUP:
            if (record->event.pressed) {
                int i;
                for (i = 1; i <= 5; ++i) {
                    // tap_code(KC_VOLU) doesn't work w/ Planck
                    tap_code(KC__VOLUP);
                }
            }
            break;
        case OSHR:
            if (record->event.pressed) {
                set_oneshot_layer(BASE_HRM, ONESHOT_START);
            }
            break;
        case OOPS:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_H)); // Hide Active Window
                // KC_MUTE will toggle on double tap which isn't ideal here
                int i;
                for (i = 1; i <= 20; ++i) {
                    // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
                    tap_code(KC__VOLDOWN); // Mute audio (needed for Planck, not sure why)
                }
            }
            break;
        case MO(LOWEST):
           if (record->event.pressed) {
                if (MODS_LCTRL || MODS_LALT || MODS_LGUI) {
                    layer_on(BASE);
                    register_mods(MOD_BIT(KC_LSFT));
                } else {
                    return true;
                }
            } else {
                if (MODS_LSFT) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                }
                if (IS_LAYER_ON(LOWEST)) {
                    layer_off(LOWEST);
                }
            }
            return false;
            break;
        case KC_LGUI:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LOWEST)) {
                    layer_off(LOWEST);
                    register_mods(MOD_BIT(KC_LSFT));
                }
            } else {
                if (MODS_LSFT && !MODS_LCTRL && !MODS_LALT && MODS_LGUI) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                    layer_on(LOWEST);
                }
            }
            break;
        case KC_LALT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LOWEST)) {
                    layer_off(LOWEST);
                    register_mods(MOD_BIT(KC_LSFT));
                }
            } else {
                if (MODS_LSFT && !MODS_LCTRL && MODS_LALT && !MODS_LGUI) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                    layer_on(LOWEST);
                }
            }
            break;
        case KC_LCTL:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LOWEST)) {
                    layer_off(LOWEST);
                    register_mods(MOD_BIT(KC_LSFT));
                }
            } else {
                if (MODS_LSFT && MODS_LCTRL && !MODS_LALT && !MODS_LGUI) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                    layer_on(LOWEST);
                }
            }
            break;
        case LT(HIGHEST,KC_LEFT):
            if (record->event.pressed) {
                if (MODS_RCTRL || MODS_RALT || MODS_RGUI) {
                    layer_on(BASE);
                    register_mods(MOD_BIT(KC_RSFT));
                } else {
                    return true;
                }
            } else {
                if (MODS_RSFT) {
                    unregister_mods(MOD_BIT(KC_RSFT));
                }
                if (IS_LAYER_ON(HIGHEST)) {
                    layer_off(HIGHEST);
                }
            }
            return false;
            break;
        case KC_RGUI:
        case KC_RALT:
        case KC_RCTL:
            if (record->event.pressed) {
                if (IS_LAYER_ON(HIGHEST)) {
                    layer_off(HIGHEST);
                    register_mods(MOD_BIT(KC_RSFT));
                }
            }
            break;
        case RGUI_T(KC_DOWN):
            if (!record->event.pressed) {
                if (MODS_RSFT && !MODS_RCTRL && !MODS_RALT && MODS_RGUI) {
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHEST);
                }
            }
            break;
        case RALT_T(KC_UP):
            if (!record->event.pressed) {
                if (MODS_RSFT && !MODS_RCTRL && MODS_RALT && !MODS_RGUI) {
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHEST);
                }
            }
            break;
        case RCTL_T(KC_RIGHT):
            if (!record->event.pressed) {
                if (MODS_RSFT && MODS_RCTRL && !MODS_RALT && !MODS_RGUI) {
                    unregister_mods(MOD_BIT(KC_RSFT));
                    layer_on(HIGHEST);
                }
            }
            break;
    }
    return true;
}


LEADER_EXTERNS();

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > cmd_tab_timer_timeout && !is_cmd_tab_held) {
        unregister_mods(MOD_BIT(KC_LGUI));
        is_cmd_tab_active = false;
        cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
    }
  }
  // Leaders
   LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_L) {
      // Alfred
      tap_code16(LALT(KC_SPC));
    }
    SEQ_ONE_KEY(KC_T) {
      // iTerm
      tap_code16(LCTL(KC_SPC));
    }
    SEQ_TWO_KEYS(KC_Y, KC_D) {
      SEND_STRING("yarn dev");
    }
    SEQ_TWO_KEYS(KC_Y, KC_I) {
      SEND_STRING("yarn install");
    }
    SEQ_TWO_KEYS(KC_G, KC_P) {
      SEND_STRING("git pull");
    }
  }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case MO(LOWEST):
        // case MO(LOWER):
        // case MO(HIGHER):
        // case LT(HIGHEST,KC_LEFT):
        // case LT(LOW,KC_SPC):
        // case LT(HIGH,KC_ENT):
        // case LT(OS,KC_ESC):
            // return TAPPING_SLOW_TERM;
        case TD(TD_TGL_SEL):
        case TD(TD_CAPS_WORD):
        case TD(TD_CAPS_SENTENCE):
            return TAPPING_TD_TERM;
        // case LT(HIGHEST,KC_LEFT):
        // case RGUI_T(KC_DOWN):
        // case RALT_T(KC_UP):
        // case RCTL_T(KC_RIGHT):
        //     return TAPPING_TD_FAST_TERM;
        // Using retro tapping with the following
        case LT(LOW,KC_SPC):
        case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
            return TAPPING_FAST_TERM;
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOW,KC_SPC):
        case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
        case LT(HIGHEST,KC_LEFT):
        case RGUI_T(KC_DOWN):
        case RALT_T(KC_UP):
        case RCTL_T(KC_RIGHT):
            return true;
        default:
            return false;
    }
}

// We won't be rolling through all the Layer-tap keys
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOW,KC_SPC):
        case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
            return false;
        default:
            return true;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow per key spamming (return false, default behaviour)
        case LT(HIGHEST,KC_LEFT):
        case RGUI_T(KC_DOWN):
        case RALT_T(KC_UP):
        case RCTL_T(KC_RIGHT):
            return false;
        // Force hold by default
        default:
            return true;
        }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOW,KC_SPC):
        case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
            return true;
        default:
            return false;
    }
}
