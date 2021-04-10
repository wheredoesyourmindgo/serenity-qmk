#include "wheredoesyourmindgo.h"

#ifdef CONSOLE_ENABLE
    #include "print.h"
#endif

// const uint16_t PROGMEM oshr_combo[] = {MO(LOWEST), MO(HIGHEST), COMBO_END};
// const uint16_t PROGMEM oops_combo[] = {TD(TD_LCTL), TD(TD_RCTL), COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//   [COMBO_OSHR] = COMBO_ACTION(oshr_combo),
//   [COMBO_OOPS] = COMBO_ACTION(oops_combo)
// };

// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
//     case COMBO_OOPS:
//         if (pressed) {
//             unregister_mods(MOD_BIT(KC_LCTL));
//             unregister_mods(MOD_BIT(KC_RCTL));
//             tap_code16(LGUI(KC_H)); // Hide Active Window
//             // KC_MUTE will toggle on double tap which isn't ideal here
//             int i;
//             for (i = 1; i <= 20; ++i) {
//                 tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
//                 tap_code(KC__VOLDOWN); // Mute audio (needed for Planck, not sure why)
//             }
//         }
//         break;
    // case COMBO_OSHR:
    //   if (pressed) {
    //     set_oneshot_layer(BASE_HRM, ONESHOT_START);
    //   }
    //   break;
//   }
// }

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

uint8_t cur_dance(qk_tap_dance_state_t *state);
// uint8_t grv_esc_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
// void esc_grave_finished(qk_tap_dance_state_t *state, void *user_data);
// void esc_grave_reset(qk_tap_dance_state_t *state, void *user_data);
void caps_word_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_word_reset(qk_tap_dance_state_t *state, void *user_data);
void caps_sentence_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_sentence_reset(qk_tap_dance_state_t *state, void *user_data);
// void sentence_end(qk_tap_dance_state_t *state, void *user_data);
void lgui_finished(qk_tap_dance_state_t *state, void *user_data);
void lgui_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_lgui_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_lgui_reset(qk_tap_dance_state_t *state, void *user_data);
void rgui_finished(qk_tap_dance_state_t *state, void *user_data);
void rgui_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_rgui_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_rgui_reset(qk_tap_dance_state_t *state, void *user_data);
void lalt_finished(qk_tap_dance_state_t *state, void *user_data);
void lalt_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_lalt_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_lalt_reset(qk_tap_dance_state_t *state, void *user_data);
void ralt_finished(qk_tap_dance_state_t *state, void *user_data);
void ralt_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_ralt_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_ralt_reset(qk_tap_dance_state_t *state, void *user_data);
void lctl_finished(qk_tap_dance_state_t *state, void *user_data);
void lctl_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_lctl_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_lctl_reset(qk_tap_dance_state_t *state, void *user_data);
void rctl_finished(qk_tap_dance_state_t *state, void *user_data);
void rctl_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_rctl_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_rctl_reset(qk_tap_dance_state_t *state, void *user_data);


// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // else return ABORT;
         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    if (state->count == 2) {
        if (state->interrupted || !state->pressed) return DOUBLE_TAP;
        // else return ABORT;
        else return DOUBLE_HOLD;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    if (state->count == 4) {
        if (state->interrupted || !state->pressed) return QUADRUPLE_TAP;
        else return QUADRUPLE_HOLD;
    }
    // else return ABORT;
    else return OTHER;
}

// uint8_t grv_esc_dance(qk_tap_dance_state_t *state) {
//     if (state->count >= 1) {
//         if (state->interrupted || !state->pressed) return TAP;
//         else return HOLD;
//     }
//     else return OTHER;
// }

// Create an instance of 'tap' for tap dance states
static tap caps_word_state = {
    .is_press_action = true,
    .state = 0
};
static tap caps_sentence_state = {
    .is_press_action = true,
    .state = 0
};
static tap lgui_state = {
    .is_press_action = true,
    .state = 0
};
static tap rgui_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_lgui_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_rgui_state = {
    .is_press_action = true,
    .state = 0
};
static tap lalt_state = {
    .is_press_action = true,
    .state = 0
};
static tap ralt_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_lalt_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_ralt_state = {
    .is_press_action = true,
    .state = 0
};
static tap lctl_state = {
    .is_press_action = true,
    .state = 0
};
static tap rctl_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_lctl_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_rctl_state = {
    .is_press_action = true,
    .state = 0
};

// void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         // Double tapping TD_DOT produces
//         // ". <one-shot-shift>" i.e. dot, space and capitalize next letter.
//         // This helps to quickly end a sentence and begin another one
//         // without having to hit shift.
//         case 2:
//             /* Check that Shift is inactive */
//             if (!(get_mods() & MOD_MASK_SHIFT)) {
//                 tap_code(KC_SPC);
//                 /* Internal code of OSM(MOD_LSFT) */
//                 add_oneshot_mods(MOD_BIT(KC_LSHIFT));
//             } else {
//                 // send ">" (KC_DOT + shift → ">")
//                 tap_code(KC_DOT);
//             }
//             break;

//         // Since `sentence_end` is called on each tap
//         // and not at the end of the tapping term,
//         // the third tap needs to cancel the effects
//         // of the double tap in order to get the expected
//         // three dots ellipsis.
//         case 3:
//             // remove the added space of the double tap case
//             tap_code(KC_BSPC);
//             // replace the space with a second dot
//             tap_code(KC_DOT);
//             // tap the third dot
//             tap_code(KC_DOT);
//             break;

//         // send KC_DOT on every normal tap of TD_DOT
//         default:
//             tap_code(KC_DOT);
//     }
// };

// static tap esc_grave_state = {
//     .is_press_action = true,
//     .state = 0
// };

// void esc_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
//     esc_grave_state.state = grv_esc_dance(state);
//     switch (esc_grave_state.state) {
//         case HOLD:
//             register_code(KC_ESC);
//             break;
//         case TAP: {
//             int ct = state->count;
//             int i;
//             for (i = 1; i <= ct; ++i) {
//                 tap_code(KC_GRV);
//             }
//             break;
//         }
//     }
// }

// void esc_grave_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (esc_grave_state.state) {
//         case HOLD:
//             unregister_code(KC_ESC);
//             break;
//     }
//     esc_grave_state.state = 0;
// }



bool caps_active = false;
bool caps_word_active = false;
bool caps_sentence_active = false;
void caps_word_finished(qk_tap_dance_state_t *state, void *user_data) {
    caps_word_state.state = cur_dance(state);
    switch (caps_word_state.state) {
        case DOUBLE_TAP:
        case TRIPLE_TAP:
        case QUADRUPLE_TAP:
            if (!caps_active && !caps_word_active && !caps_sentence_active) {
                caps_active = true;
                caps_word_active = true;
                tap_code(KC_CAPSLOCK);
            }
            break;
        default:
            register_mods(MOD_BIT(KC_LSFT));
            break;
    }
}

void caps_word_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (caps_word_state.state) {
        case DOUBLE_TAP:
        case TRIPLE_TAP:
        case QUADRUPLE_TAP:
            break;
        default:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
    }
    caps_word_state.state = 0;
}


void caps_sentence_finished(qk_tap_dance_state_t *state, void *user_data) {
    caps_sentence_state.state = cur_dance(state);
    switch (caps_sentence_state.state) {
        case DOUBLE_TAP:
        case TRIPLE_TAP:
        case QUADRUPLE_TAP:
            if (!caps_active && !caps_sentence_active && !caps_word_active) {
                caps_active = true;
                caps_sentence_active = true;
                tap_code(KC_CAPSLOCK);
            }
            break;
        default:
            register_mods(MOD_BIT(KC_RSFT));
            break;
    }
}

void caps_sentence_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (caps_sentence_state.state) {
        case DOUBLE_TAP:
        case TRIPLE_TAP:
        case QUADRUPLE_TAP:
            break;
        default:
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
    }
    caps_sentence_state.state = 0;
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

void lgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    lgui_state.state = cur_dance(state);
    switch (lgui_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            layer_on(SFT_BASE);
            break;
    }
}

void lgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (lgui_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            layer_off(SFT_BASE);
            break;
    }
    lgui_state.state = 0;
}

void sft_lgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_lgui_state.state = cur_dance(state);
    switch (sft_lgui_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            register_mods(MOD_BIT(KC_LSFT));
            layer_off(LOWEST);
            break;
    }
}

void sft_lgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_lgui_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
    }
    sft_lgui_state.state = 0;
}

void rgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    rgui_state.state = cur_dance(state);
    switch (rgui_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI));
            layer_on(SFT_BASE);
            break;
    }
}

void rgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rgui_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI));
            layer_off(SFT_BASE);
            break;
    }
    rgui_state.state = 0;
}

void sft_rgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_rgui_state.state = cur_dance(state);
    switch (sft_rgui_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI));
            register_mods(MOD_BIT(KC_RSFT));
            layer_off(HIGHEST);
            break;
    }
}

void sft_rgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_rgui_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI));
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
    }
    sft_rgui_state.state = 0;
}

void lalt_finished(qk_tap_dance_state_t *state, void *user_data) {
    lalt_state.state = cur_dance(state);
    switch (lalt_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            layer_on(SFT_BASE);
            break;
    }
}

void lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (lalt_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            layer_off(SFT_BASE);
            break;
    }
    lalt_state.state = 0;
}

void sft_lalt_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_lalt_state.state = cur_dance(state);
    switch (sft_lalt_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            register_mods(MOD_BIT(KC_LSFT));
            layer_off(LOWEST);
            break;
    }
}

void sft_lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_lalt_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
    }
    sft_lalt_state.state = 0;
}

void ralt_finished(qk_tap_dance_state_t *state, void *user_data) {
    ralt_state.state = cur_dance(state);
    switch (ralt_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RALT));
            layer_on(SFT_BASE);
            break;
    }
}

void ralt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ralt_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RALT));
            layer_off(SFT_BASE);
            break;
    }
    ralt_state.state = 0;
}

void sft_ralt_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_ralt_state.state = cur_dance(state);
    switch (sft_ralt_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RALT));
            register_mods(MOD_BIT(KC_RSFT));
            layer_off(HIGHEST);
            break;
    }
}

void sft_ralt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_ralt_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RALT));
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
    }
    sft_ralt_state.state = 0;
}

void lctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    lctl_state.state = cur_dance(state);
    switch (lctl_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            layer_on(SFT_BASE);
            break;
    }
}

void lctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (lctl_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            layer_off(SFT_BASE);
            break;
    }
    lctl_state.state = 0;
}

void sft_lctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_lctl_state.state = cur_dance(state);
    switch (sft_lctl_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            register_mods(MOD_BIT(KC_LSFT));
            layer_off(LOWEST);
            break;
    }
}

void sft_lctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_lctl_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
    }
    sft_lctl_state.state = 0;
}

void rctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    rctl_state.state = cur_dance(state);
    switch (rctl_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            layer_on(SFT_BASE);
            break;
    }
}

void rctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rctl_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            layer_off(SFT_BASE);
            break;
    }
    rctl_state.state = 0;
}

void sft_rctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_rctl_state.state = cur_dance(state);
    switch (sft_rctl_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            register_mods(MOD_BIT(KC_RSFT));
            layer_off(HIGHEST);
            break;
    }
}

void sft_rctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sft_rctl_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
    }
    sft_rctl_state.state = 0;
}

// Tap once for Word Select, twice for Line Select, three times for all
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(tgl_select, NULL, NULL),
    [TD_CAPS_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_word_finished, caps_word_reset),
    [TD_CAPS_SENTENCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_sentence_finished, caps_sentence_reset),
    [TD_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_finished, lgui_reset),
    [TD_SFT_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_lgui_finished, sft_lgui_reset),
    [TD_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_finished, rgui_reset),
    [TD_SFT_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_rgui_finished, sft_rgui_reset),
    [TD_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_finished, lalt_reset),
    [TD_SFT_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_lalt_finished, sft_lalt_reset),
    [TD_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_finished, ralt_reset),
    [TD_SFT_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_ralt_finished, sft_ralt_reset),
    [TD_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_finished, lctl_reset),
    [TD_SFT_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_lctl_finished, sft_lctl_reset),
    [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_finished, rctl_reset),
    [TD_SFT_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_rctl_finished, sft_rctl_reset),
    // [TD_G_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(sentence_end, NULL, NULL)
    // [TD_ESC_GRAVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_grave_finished, esc_grave_reset)
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
// #define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
// #define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))
// #define MODS_GUI (get_mods() & MOD_BIT(KC_LGUI) || get_mods() & MOD_BIT(KC_RGUI))
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
                caps_sentence_active = false;
                caps_word_active = false;
                if (caps_active) {
                    caps_active = false;
                } else {
                    caps_active = true;
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
        // Space, colon, semi-colon, comma cancel caps word
        case KC_SPC:
        case LT(LOW,KC_SPC):
        case KC_COLN:
        case KC_SCLN:
        case KC_COMM:
            if (record->event.pressed) {
                cancel_caps_word();
            }
            break;
        // Tab, enter, period (and escape) cancel caps word and caps sentence
        case KC_TAB:
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
    }
    return true;
}


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case MO(LOWEST):
        // case MO(LOWER):
        // case MO(HIGHER):
        // case MO(HIGHEST):
        // case LT(LOW,KC_SPC):
        // case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
            return TAPPING_SLOW_TERM;
        case TD(TD_TGL_SEL):
        case TD(TD_CAPS_WORD):
        case TD(TD_CAPS_SENTENCE):
            return TAPPING_TD_TERM;
        case TD(TD_LGUI):
        case TD(TD_RGUI):
        case TD(TD_SFT_LGUI):
        case TD(TD_SFT_RGUI):
        case TD(TD_LALT):
        case TD(TD_RALT):
        case TD(TD_SFT_LALT):
        case TD(TD_SFT_RALT):
        case TD(TD_LCTL):
        case TD(TD_RCTL):
        case TD(TD_SFT_LCTL):
        case TD(TD_SFT_RCTL):
            return 0;
        // case TD(TD_ESC_GRAVE):
        //     return 180;
        default:
            return TAPPING_TERM;
    }
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

    SEQ_ONE_KEY(KC_S) {
      // Alfred
      tap_code16(LALT(KC_SPC));
    }
    SEQ_ONE_KEY(KC_SPC) {
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


// Allow Permissive Hold on thumb keys
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOW,KC_SPC):
        case LT(HIGH,KC_ENT):
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

// Allow per key spamming
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
        // case LT(LOW,KC_SPC):
        // case LT(HIGH,KC_ENT):
        case LT(OS,KC_ESC):
        case TD(TD_TGL_SEL): // required for proper toggle select behavior
        case TD(TD_CAPS_WORD):
        case TD(TD_CAPS_SENTENCE):
        case TD(TD_LGUI):
        case TD(TD_SFT_LGUI):
        case TD(TD_RGUI):
        case TD(TD_SFT_RGUI):
        case TD(TD_LALT):
        case TD(TD_SFT_LALT):
        case TD(TD_RALT):
        case TD(TD_SFT_RALT):
        case TD(TD_LCTL):
        case TD(TD_SFT_LCTL):
        case TD(TD_RCTL):
        case TD(TD_SFT_RCTL):
        // case TD(TD_G_DOT):
            return false;
        default:
            return true;
    }
}
