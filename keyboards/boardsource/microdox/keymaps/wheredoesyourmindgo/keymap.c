// #include "split_util.h"
#include "keymap.h"

const uint16_t PROGMEM spc_tab_combo[] = {LT_NAVR_ESC, LT(MOUR,KC_SPC), COMBO_END};
const uint16_t PROGMEM esc_spc_combo[] = {LT(MEDR,KC_TAB), LT_NAVR_ESC, COMBO_END};
const uint16_t PROGMEM esc_spc_fcs_combo[] = {LT_MDR_FCS_TAB, LT_NAVR_ESC, COMBO_END};
const uint16_t PROGMEM a_z_combo[] = {LCTL_T(KC_A), LT(OS,KC_Z), COMBO_END};
const uint16_t PROGMEM a_z_fcs_combo[] = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM q_a_combo[] = {KC_Q, LCTL_T(KC_A), COMBO_END};
const uint16_t PROGMEM q_a_fcs_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM ent_bspc_combo[] = {LT(NSSL,KC_BSPC),LT(NSL,KC_ENT), COMBO_END};
const uint16_t PROGMEM bspc_del_combo[] = {LT(NSL,KC_ENT), LT(FUNL,KC_DEL), COMBO_END};
const uint16_t PROGMEM o_slsh_combo[] = {LCTL_T(KC_O), LT(WNDW,KC_SLSH), COMBO_END};
const uint16_t PROGMEM o_slsh_fcs_combo[] = {KC_O, KC_SLSH, COMBO_END};
const uint16_t PROGMEM quot_o_combo[] = {KC_QUOT, LCTL_T(KC_O), COMBO_END};
const uint16_t PROGMEM quot_o_fcs_combo[] = {KC_QUOT, KC_O, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SPC_TAB__GUI] = COMBO(spc_tab_combo, KC_LGUI),
  [ESC_SPC__ALT] = COMBO(esc_spc_combo, KC_LALT),
  [A_Z__SFT] = COMBO(a_z_combo, KC_LSFT),
  [Q_A__CTL] = COMBO(q_a_combo, KC_LCTL),
  [ENT_BSPC__GUI] = COMBO(ent_bspc_combo, KC_LGUI),
  [BSPC_DEL__ALT] = COMBO(bspc_del_combo, KC_LALT),
  [O_SLSH__SFT] = COMBO(o_slsh_combo, KC_LSFT),
  [QUOT_O__CTL] = COMBO(quot_o_combo, KC_LCTL),
  [ESC_SPC_FCS__ALT] = COMBO(esc_spc_fcs_combo, KC_LALT),
  [A_Z_FCS__SFT] = COMBO(a_z_fcs_combo, KC_LSFT),
  [Q_A_FCS__CTL] = COMBO(q_a_fcs_combo, KC_LCTL),
  [O_SLSH_FCS__SFT] = COMBO(o_slsh_fcs_combo, KC_LSFT),
  [QUOT_O_FCS__CTL] = COMBO(quot_o_fcs_combo, KC_LCTL)
};
// end of Combos

// Tap Dance declarations

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void tgl_sel_finished(qk_tap_dance_state_t *state, void *user_data);
void tgl_sel_reset(qk_tap_dance_state_t *state, void *user_data);
void esc_grave_finished(qk_tap_dance_state_t *state, void *user_data);
void esc_grave_reset(qk_tap_dance_state_t *state, void *user_data);
void tab_bs_finished(qk_tap_dance_state_t *state, void *user_data);
void tab_bs_reset(qk_tap_dance_state_t *state, void *user_data);

// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    if (state->count == 2) {
        if (state->interrupted || !state->pressed) return DOUBLE_TAP;
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

static tap esc_grave_state = {
    .is_press_action = true,
    .state = 0
};

static tap tab_bs_state = {
    .is_press_action = true,
    .state = 0
};

// Create an instance of 'tap' for the 'x' tap dance.
static tap tgl_sel_state = {
    .is_press_action = true,
    .state = 0
};

void esc_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
    esc_grave_state.state = cur_dance(state);
    switch (esc_grave_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUADRUPLE_HOLD:
            register_code(KC_ESC);
            break;
        default:
            if (state->interrupted || !state->pressed) {
                int ct = state->count;
                int i;
                for (i = 1; i <= ct; ++i) {
                    tap_code(KC_GRV);
                }
            }
            break;
    }
}

void esc_grave_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (esc_grave_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUADRUPLE_HOLD:
            unregister_code(KC_ESC);
            break;
    }
    esc_grave_state.state = 0;
}

void tab_bs_finished(qk_tap_dance_state_t *state, void *user_data) {
    tab_bs_state.state = cur_dance(state);
    switch (tab_bs_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUADRUPLE_HOLD:
            register_code(KC_TAB);
            break;
        default:
            if (state->interrupted || !state->pressed) {
                int ct = state->count;
                int i;
                for (i = 1; i <= ct; ++i) {
                    tap_code(KC_BSLS);
                }
            }
            break;
    }
}

void tab_bs_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tab_bs_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUADRUPLE_HOLD:
            unregister_code(KC_TAB);
            break;
    }
    tab_bs_state.state = 0;
}



void tgl_sel_finished(qk_tap_dance_state_t *state, void *user_data) {
    tgl_sel_state.state = cur_dance(state);
    switch (tgl_sel_state.state) {
        case OTHER: break;
        case SINGLE_TAP:
            tap_code16(LALT(KC_LEFT));
            tap_code16(LALT(LSFT(KC_RGHT)));
            break;
        case DOUBLE_TAP:
            tap_code16(LGUI(KC_LEFT));
            tap_code16(LGUI(LSFT(KC_RGHT)));
            break;
        case TRIPLE_TAP:
            tap_code16(LGUI(KC_UP));
            tap_code16(LGUI(LSFT(KC_DOWN)));
            break;
    }
}

void tgl_sel_reset(qk_tap_dance_state_t *state, void *user_data) {
    tgl_sel_state.state = 0;
}

// Tap once for Word Select, twice for Line Select
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tgl_sel_finished, tgl_sel_reset),
    [TD_ESC_GRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_grave_finished, esc_grave_reset),
    [TD_TAB_BS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_bs_finished, tab_bs_reset)
};
// end of Tap Dance config


// Compensate for slow thumbs.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT_NAVR_ESC:
        //     return TAPPING_THUMB_TERM;
        // case LT(MOUR,KC_SPC):
        //     return TAPPING_THUMB_TERM;
        // case LT(MEDR,KC_TAB):
        //     return TAPPING_THUMB_TERM;
        // case LT_MDR_FCS_TAB:
        //     return TAPPING_THUMB_TERM;
        // case LT(NSL,KC_ENT):
        //     return TAPPING_THUMB_TERM;
        // case LT(NSSL,KC_BSPC):
        //     return TAPPING_THUMB_TERM;
        // case LT(FUNL,KC_DEL):
        //     return TAPPING_THUMB_TERM;
        case TD(TD_TGL_SEL):
            return TAPPING_TD_TERM;
        default:
            return TAPPING_TERM;
    }
}

// Allow Permissive Hold on thumb keys.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_NAVR_ESC:
            return true;
        case LT(MOUR,KC_SPC):
            return true;
        case LT(MEDR,KC_TAB):
            return true;
        case LT_MDR_FCS_TAB:
            return true;
        case LT(NSL,KC_ENT):
            return true;
        case LT(NSSL,KC_BSPC):
            return true;
        case LT(FUNL,KC_DEL):
            return true;
        default:
            return false;
    }
}

// I won't be rolling through the thumb keys
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_NAVR_ESC:
            return false;
        case LT(MOUR,KC_SPC):
            return false;
        case LT(MEDR,KC_TAB):
            return false;
        case LT_MDR_FCS_TAB:
            return false;
        case LT(NSL,KC_ENT):
            return false;
        case LT(NSSL,KC_BSPC):
            return false;
        case LT(FUNL,KC_DEL):
            return false;
        default:
            return true;
    }
}

// Allow per key spamming
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
        // case LT(MEDR,KC_TAB):
        // case LT_MDR_FCS_TAB:
        // case LT_NAVR_ESC:
        // case LT(MOUR,KC_SPC):
        // case LT(NSSL,KC_BSPC):
        // case LT(NSL,KC_ENT):
        // case LT(FUNL,KC_DEL):
        case TD(TD_TGL_SEL): // required for proper toggle select behavior
            return false;
        default:
            return true;
    }
}

/* Macros */
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;
#define cmd_tab_timer_default_dur 1000;
#define cmd_tab_timer_fast_dur 600;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB_NXT:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_mods(MOD_BIT(KC_LGUI));
        } else {
            // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
            cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case CMD_TAB_PRV:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LGUI);
          // First tap will do the same thing as CMD_TAB_NXT since the order gets rearranged on last window active. Subsequent taps will move the selection backwards.
          register_code(KC_TAB);
        } else {
            register_mods(MOD_BIT(KC_LSFT));
            register_code(KC_TAB);
            // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
            cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
        }
        cmd_tab_timer = timer_read();
      } else {
        unregister_mods(MOD_BIT(KC_LSFT));
        unregister_code(KC_TAB);
      }
      break;
    case LT(OS,KC_Z):
        // Immediately end cmd+tab when OS Layer-tap is released
        if (!record->event.pressed) {
            if (is_cmd_tab_active) {
                unregister_mods(MOD_BIT(KC_LGUI));
                is_cmd_tab_active = false;
                cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
            }
        }
        break;
    case OOPS:
        if (record->event.pressed) {
            tap_code16(LGUI(KC_H)); // Hide Active Window
            // KC_MUTE will toggle on double tap which isn't ideal here
            int i;
            for (i = 1; i <= 20; ++i) {
                tap_code(KC_VOLD); // Mute audio
            }
        }


  }
  return true;
}

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > cmd_tab_timer_timeout) {
        unregister_mods(MOD_BIT(KC_LGUI));
        is_cmd_tab_active = false;
        cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
    }
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_split_3x5_3(
        KC_Q,  KC_W,    KC_F,           KC_P,               KC_B,               KC_J,               KC_L,               KC_U,               KC_Y,           KC_QUOT,
        LCTL_T(KC_A),   LALT_T(KC_R),   LGUI_T(KC_S),       LSFT_T(KC_T),       KC_G,               KC_M,               LSFT_T(KC_N),       LGUI_T(KC_E),   LALT_T(KC_I),   LCTL_T(KC_O),
        LT(OS,KC_Z),    RALT_T(KC_X),   KC_C,               KC_D,               KC_V,               KC_K,               KC_H,               KC_COMM,        RALT_T(KC_DOT), LT(WNDW,KC_SLSH),
                                        LT(MEDR,KC_TAB),    LT_NAVR_ESC,        LT(MOUR,KC_SPC),    LT(NSSL,KC_BSPC),   LT(NSL,KC_ENT),     LT(FUNL,KC_DEL)
    ),
	[FCS] = LAYOUT_split_3x5_3(
        KC_Q,           KC_W,           KC_F,               KC_P,               KC_B,               KC_J,               KC_L,               KC_U,           KC_Y,           KC_QUOT,
        KC_A,           KC_R,           KC_S,               KC_T,               KC_G,               KC_M,               KC_N,               KC_E,           KC_I,           KC_O,
        KC_Z,           KC_X,           KC_C,               KC_D,               KC_V,               KC_K,               KC_H,               KC_COMM,        KC_DOT,         KC_SLSH,
                                        LT_MDR_FCS_TAB,     LT_NAVR_ESC,        LT(MOUR,KC_SPC),    LT(NSSL,KC_BSPC),   LT(NSL,KC_ENT),     LT(FUNL,KC_DEL)
    ),
	[NAVR] = LAYOUT_split_3x5_3(
        RESET,          DEBUG,          KC_NO,              KC_NO,              KC_NO,              SGUI(KC_Z),         LGUI(KC_V),         LGUI(KC_C),     LGUI(KC_X),     LGUI(KC_Z),
        KC_LCTL,        KC_LALT,        KC_LGUI,            KC_LSFT,            DF(NAVR),           TD(TD_TGL_SEL),     KC_LEFT,            KC_DOWN,        KC_UP,          KC_RGHT,
        KC_NO,          KC_RALT,        KC_NO,              KC_NO,              KC_NO,              KC_INS,             KC_HOME,            KC_PGDN,        KC_PGUP,        KC_END,
                                        KC_NO,              DF(BASE),           KC_NO,              KC_BSPC,            KC_ENT,             KC_DEL
    ),
	[MOUR] = LAYOUT_split_3x5_3(
        RESET,          DEBUG,          KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_BTN1,            KC_BTN3,        KC_BTN2,        KC_NO,
        KC_LCTL,        KC_LALT,        KC_LGUI,            KC_LSFT,            DF(MOUR),           KC_NO,              KC_MS_L,            KC_MS_D,        KC_MS_U,        KC_MS_R,
        KC_NO,          KC_RALT,        KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_WH_L,            KC_WH_U,        KC_WH_D,        KC_WH_R,
                                        KC_NO,              KC_NO,              DF(BASE),           KC_NO,              KC_NO,              KC_NO
    ),
	[MEDR] = LAYOUT_split_3x5_3(
        RESET,          DEBUG,          KC_NO,              KC_NO,              KC_NO,              RGB_TOG,            RGB_MOD,            RGB_HUI,        RGB_SAI,        RGB_VAI,
        KC_LCTL,        KC_LALT,        KC_LGUI,            KC_LSFT,            DF(MEDR),           KC_MUTE,            KC_VOLD,            KC_F14,         KC_F15,         KC_VOLU,
        KC_NO,          KC_RALT,        KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_MRWD,            KC_MPLY,        MAC_MSTP,       KC_MFFD,
                                        DF(BASE),           KC_NO,              KC_NO,              KC_NO,              KC_CAPS,            TO(FCS)
    ),
	[MEDR_FCS] = LAYOUT_split_3x5_3(
        RESET,          DEBUG,          KC_NO,              KC_NO,              KC_NO,              RGB_TOG,            RGB_MOD,            RGB_HUI,        RGB_SAI,        RGB_VAI,
        KC_LCTL,        KC_LALT,        KC_LGUI,            KC_LSFT,            DF(MEDR_FCS),       KC_MUTE,            KC_VOLD,            KC_F14,         KC_F15,         KC_VOLU,
        KC_NO,          KC_RALT,        KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_MRWD,            KC_MPLY,        MAC_MSTP,       KC_MFFD,
                                        DF(FCS),            KC_NO,              KC_NO,              KC_NO,              KC_CAPS,            TO(BASE)
    ),
	[NSL] = LAYOUT_split_3x5_3(
        KC_1,           KC_2,           KC_3,               KC_4,               KC_5,               KC_NO,              KC_NO,              KC_NO,          DEBUG,          RESET,
        KC_6,           KC_7,           KC_8,               KC_9,               KC_0,               DF(NSL),            KC_LSFT,            KC_LGUI,        KC_LALT,        KC_LCTL,
        KC_SCLN,        KC_MINS,        KC_EQL,             KC_LBRC,            KC_RBRC,            KC_NO,              KC_NO,              KC_NO,          KC_RALT,        KC_NO,
                                        TD(TD_TAB_BS),      TD(TD_ESC_GRV),     KC_SPC,             KC_NO,              DF(BASE),           KC_NO
    ),
	[NSSL] = LAYOUT_split_3x5_3(
        KC_EXLM,        KC_AT,          KC_HASH,            KC_DLR,             KC_PERC,            KC_NO,              KC_NO,              KC_NO,          DEBUG,          RESET,
        KC_CIRC,        KC_AMPR,        KC_ASTR,            KC_LPRN,            KC_RPRN,            DF(NSSL),           KC_LSFT,            KC_LGUI,        KC_LALT,        KC_LCTL,
        KC_COLN,        KC_UNDS,        KC_PLUS,            KC_LCBR,            KC_RCBR,            KC_NO,              KC_NO,              KC_NO,          KC_RALT,        KC_NO,
                                        KC_PIPE,            KC_TILD,            KC_SPC,             DF(BASE),           KC_NO,              KC_NO
    ),
	[FUNL] = LAYOUT_split_3x5_3(
        KC_F1,          KC_F2,          KC_F3,              KC_F4,              KC_F5,              KC_NO,              KC_NO,              KC_NO,          DEBUG,          RESET,
        KC_F6,          KC_F7,          KC_F8,              KC_F9,              KC_F10,             DF(FUNL),           KC_LSFT,            KC_LGUI,        KC_LALT,        KC_LCTL,
        KC_F11,         KC_F12,         KC_F13,             KC_F14,             KC_F15,             KC_NO,              KC_NO,              KC_NO,          KC_RALT,        KC_NO,
                                        KC_PSCR,            KC_SLCK,            KC_PAUS,            KC_NO,              KC_NO,              DF(BASE)
    ),
	[OS] = LAYOUT_split_3x5_3(
        KC_NO,          KC_NO,          KC_NO,              KC_NO,              KC_NO,              OS_SCRN_SHT_OPT,    OS_SPTLGHT,         OS_LNCHPD,          OS_SIRI,            OS_SDBR,
        KC_NO,          OOPS,           OOPS,               OOPS,               KC_NO,              OS_FLLSCRN,         OS_PRV_SPC,         CMD_TAB_PRV,        CMD_TAB_NXT,        OS_NXT_SPC,
        KC_NO,          KC_NO,          KC_NO,              KC_NO,              KC_NO,              OS_DSKTP,           OS_MSN_CNTRL,       OS_PRVS_APP_WNDW,   OS_NXT_APP_WNDW,    OS_APP_WNDWS,
                                        KC_NO,              KC_NO,              KC_NO,              KC_APP,             KC_NO,              KC_NO
    ),
	[WNDW] = LAYOUT_split_3x5_3(
        KC_NO,          KC_NO,          KC_NO,              KC_NO,              KC_NO,               WNDW_LRGR,         LCA(KC_U),          WNDW_TOP_HLF,       LCA(KC_I),      WNDW_MAX,
        KC_NO,          KC_NO,          KC_NO,              KC_NO,              KC_NO,               WNDW_CNTR,         WNDW_LFT_HLF,       WNDW_CNTR_HLF,      WNDW_RGHT_HLF,  WNDW_ALMST_MAX,
        KC_NO,          KC_NO,          KC_NO,              KC_NO,              KC_NO,               WNDW_SMLLR,        LCA(KC_J),          WNDW_BTTM_HLF,      LCA(KC_K),      WNDW_VRT_MAX,
                                        KC_NO,              LCA(KC_MINS),       LCA(KC_EQL),         WNDW_RSTR,         LCA(KC_E),          LCA(KC_T)
    )
};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(qmk_logo, false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR(OLED_RENDER_MODS_CTL), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_MODS_ALT), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_MODS_GUI), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_MODS_SFT), (modifiers & MOD_MASK_SHIFT));
}

static void render_status(void) {
    switch (get_highest_layer(default_layer_state | layer_state)) {
        case BASE:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("^\n"), false);
            oled_write_P(PSTR("Layer: Base\n"), false);
            break;
        case NAVR:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("  ^\n"), false);
            oled_write_P(PSTR("Layer: Navigation\n"), false);
            break;
        case MOUR:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("    ^\n"), false);
            oled_write_P(PSTR("Layer: Mouse\n"), false);
            break;
        case MEDR:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("      ^\n"), false);
            oled_write_P(PSTR("Layer: Media\n"), false);
            break;
        case MEDR_FCS:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("      ^\n"), false);
            oled_write_P(PSTR("Layer: Media\n"), false);
            break;
        case NSL:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("        ^\n"), false);
            oled_write_P(PSTR("Layer: Number\n"), false);
            break;
        case NSSL:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("          ^\n"), false);
            oled_write_P(PSTR("Layer: Symbol\n"), false);
            break;
        case FUNL:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("            ^\n"), false);
            oled_write_P(PSTR("Layer: Function\n"), false);
            break;
        case OS:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("              ^\n"), false);
            oled_write_P(PSTR("Layer: OS\n"), false);
            break;
        case WNDW:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("                ^\n"), false);
            oled_write_P(PSTR("Layer: Window\n"), false);
            break;
        case FCS:
            // oled_write_P(PSTR("B N M M N S F O W\n"), false);
            // oled_write_P(PSTR("                ^\n"), false);
            oled_write_P(PSTR("Layer: Focus\n"), false);
            break;
        default:
            // oled_write_P(PSTR("B N M M N S F O W"), false);
            // oled_write_P(PSTR("        ^\n"), false);
            oled_write_P(PSTR("Layer: Other\n"), false);
    }
}


void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
        oled_write_P(PSTR("\n"), false);
        render_mod_status(get_mods() | get_oneshot_mods());
    } else {
        render_logo();
        oled_scroll_left();
        // render_status();
    }
}

#endif
