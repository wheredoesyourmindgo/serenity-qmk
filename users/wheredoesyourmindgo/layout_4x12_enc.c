
#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_4x12_enc(
        KC_DEL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        TD(TD_OS_GRV), ALPH_R2C1, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, ALPH_R2C10, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LALT, KC_LGUI, LT(LOWEST, KC_APP), TD(TD_LOWER_ESC), TD(TD_LOW_ENT), KC_MUTE,  LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), LT(HIGHEST,KC_LEFT), RGUI_T(KC_DOWN), RALT_T(KC_UP), RCTL_T(KC_RIGHT)
    ),
    [BASE_QWRTY] = LAYOUT_4x12_enc(
        KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        TD(TD_OS_GRV), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LALT, KC_LGUI, LT(LOWEST, KC_APP), TD(TD_LOWER_ESC), TD(TD_LOW_ENT), KC_MUTE,  LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), LT(HIGHEST,KC_LEFT), RGUI_T(KC_DOWN), RALT_T(KC_UP), RCTL_T(KC_RIGHT)
    ),
    // Having LT(HIGHER,KC_SPC) allows quick toggle select when arrowing with Lower layer
	[LOWER] = LAYOUT_4x12_enc(
        KC_DEL , KC_1         , KC_2         , KC_3         , KC_4         , KC_5     ,         KC_6          , KC_7   , KC_8 , KC_9, KC_0, TRY_BSPACE_WORD,
        KC_GRV , XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOWER), KC_DOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        MO(LOWER_ALT), KC_NO        , OSM(MOD_RALT)      , KC_NO        , VOID        , KC_NO    ,          KC_NO  , KC_HOME, KC_PGDN, KC_PGUP, KC_END, RSFT_T(KC_CAPS),
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT        , DF(BASE)     , KC_ENT   , KC_TRNS, KC_TAB, LT(HIGHER,KC_SPC),  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[LOWER_ALT] = LAYOUT_4x12_enc(
        KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS         ,   KC_TRNS, KC_TRNS, KC_TRNS          , OS_PRV_TAB, KC_TRNS, KC_TRNS, OS_NXT_TAB, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(LOWER_ALT),    KC_TRNS, OS_BCK, OS_FWD_FLDR, OS_BCK_FLDR, OS_FWD, KC_TRNS,
        KC_TRNS, KC_TRNS        , KC_TRNS      , KC_TRNS        ,          KC_TRNS, KC_TRNS,       KC_TRNS  , ZOOM_RESET, ZOOM_IN, ZOOM_OUT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS        , DF(BASE)     , KC_TRNS   ,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[LOW] = LAYOUT_4x12_enc(
        KC_DEL, KC_EXLM      , KC_AT        , KC_HASH      , KC_DLR       , KC_PERC ,                  KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_ASTR, KC_BSPC,
        KC_NO, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOW),                  KC_EQL, KC_MINS , KC_LCBR, KC_RCBR, KC_PIPE, KC_QUOT,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO        , VOID        , KC_NO   ,                  KC_PLUS, KC_UNDS, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,        KC_NO        , DF(BASE),KC_TRNS, KC_TAB, KC_SPC,  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
    [LOWEST] = LAYOUT_4x12_enc(
        KC_DEL, KC_NO, KC_BTN2, KC_BTN3, KC_BTN1, KC_NO, KC_NO, KC_BTN1, KC_BTN3, KC_BTN2, KC_NO, LGUI(KC_BSPC),
        KC_NO, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOWEST), KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, VOID, KC_NO, KC_NO, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, DF(BASE), KC_NO, KC_NO,KC_TRNS, KC_NO, KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[HIGHER] = LAYOUT_4x12_enc(
        LALT(KC_DEL), OS_CLOSE_WIN, OS_CLOSE, OS_MIN, WNDW_MAX, TD(TD_TGL_SEL), KC_APP, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, KC_BSPC,
        KC_GRV, TLNG_LFT, TLNG_ILFT, TLNG_IRGHT, TLNG_RGHT, WNDW_CNTR, DF(HIGHER), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        LSFT_T(KC_CAPS), UNDO, CUT, COPY, PASTE, REDO, KC_NO, VOID, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, TD(TD_LOWER_ESC), KC_ENT,KC_TRNS, KC_TAB, DF(BASE), KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
    [HIGH] = LAYOUT_4x12_enc(
        KC_DEL,  DISP_FDIM, DISP_DIM , DISP_BRI,   DISP_FBRI, OS_DRKMD_TGL,  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,   RESET,
        KC_GRV, KC_MUTE, KC_VOLD, KC_VOLU, VOL_JUP,   KC_NO,   DF(HIGHEST),   XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DEBUG,
        KC_LSFT ,  MAC_MSTP, KC_MRWD,  KC_MFFD,  KC_MPLY,  TGL_LYT,  KC_NO, VOID, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_ESC,  KC_ENT, OS_DRKMD_TGL, DF(BASE), KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[HIGHEST] = LAYOUT_4x12_enc(
        LCTL(KC_K), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_BSPC,
        KC_NO, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, DF(HIGH), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_LSFT, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, VOID, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_NO,KC_TRNS, KC_NO, KC_NO, DF(BASE), RGUI_T(KC_DOWN), RALT_T(KC_UP), RCTL_T(KC_RIGHT)
    ),
	[OS] = LAYOUT_4x12_enc(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    OS_SCRN_SHT_OPT,  OS_LNCHPD, OS_SPTLGHT,     OS_SIRI,            OS_SDBR,    KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    PRV_APP,       OS_PRV_SPC,     CMD_TAB_PRV,        CMD_TAB_NXT,        OS_NXT_SPC,  OS_FLLSCRN,
        KC_NO, KC_NO, KC_NO, KC_NO, VOID, KC_NO,        OS_DSKTP,        OS_PRVS_APP_WNDW,OS_MSN_CNTRL, OS_APP_WNDWS, OS_NXT_APP_WNDW,   KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, DF(BASE), DF(BASE), KC_TRNS, OS_TRM_VSR,  OS_LNCHR,                     KC_NO,              KC_NO,              KC_NO,          KC_NO
    )
};

