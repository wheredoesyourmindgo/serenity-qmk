
#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_4x12(
        KC_DEL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        LT(OS,KC_GRV), ALPH_R2C1, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, ALPH_R2C10, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    ),
    [BASE_QWRTY] = LAYOUT_4x12(
        KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        LT(OS,KC_GRV), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), LT(HIGHEST, KC_SLSH), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    // Having LT(HIGHER,KC_SPC) allows quick toggle select when arrowing with Lower layer
	[LOWER] = LAYOUT_4x12(
        KC_DEL , KC_1         , KC_2         , KC_3         , KC_4         , KC_5     ,         KC_6          , KC_7   , KC_8 , KC_9, KC_0, TRY_BSPACE_WORD,
        KC_GRV , XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOWER),         KC_DOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, TGL_LOWER, OSM(MOD_RALT)      , KC_NO        , VOID        , KC_NO    ,          KC_NO  , KC_HOME, KC_PGDN, KC_PGUP, KC_END, RSFT_T(KC_CAPS),
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI,  DF(BASE)     , KC_ENT   , KC_TAB, LT(HIGHER,KC_SPC),  KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[LOWER_ALT] = LAYOUT_4x12(
        KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS         ,   KC_TRNS, KC_TRNS, ZOOM_RESET_APP, KC_TRNS, ZOOM_IN_APP, ZOOM_OUT_APP, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(LOWER_ALT),    KC_TRNS, OS_BCK, OS_FWD_FLDR, OS_BCK_FLDR, OS_FWD, KC_TRNS,
        KC_TRNS, TGL_LOWER, KC_TRNS      , KC_TRNS        ,          KC_TRNS, KC_TRNS,       ZOOM_RESET, KC_TRNS, ZOOM_IN, ZOOM_OUT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(BASE), KC_TRNS   , KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[LOW] = LAYOUT_4x12(
        KC_DEL, KC_EXLM      , KC_AT        , KC_HASH      , KC_DLR       , KC_PERC ,                  KC_CIRC, KC_AMPR, XASTR, XLPRN, XRPRN, KC_BSPC,
        KC_NO, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOW),                  KC_EQL, KC_MINS , KC_LCBR, KC_RCBR, KC_PIPE, KC_QUOT,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO        , VOID        , KC_NO   ,                  KC_PLUS, KC_UNDS, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DF(BASE), KC_TAB, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [LOWEST] = LAYOUT_4x12(
        KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BTN1_HOLD, KC_BTN1, KC_BTN3, KC_BTN2, KC_LOCK, KC_BSPC,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        DF(BASE), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, KC_ENT, DF(LOWEST), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHER] = LAYOUT_4x12(
        LALT(KC_DEL), OS_PRV_TAB, OS_PRVS_APP_WNDW, OS_NXT_APP_WNDW, OS_NXT_TAB, TD(TD_TGL_SEL), KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, KC_BSPC,
        KC_GRV,  TLNG_LFT, TLNG_ILFT,  TLNG_IRGHT, TLNG_RGHT, WNDW_MAX, DF(HIGHER), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        LSFT_T(KC_CAPS), WNDW_LFT, WNDW_ILFT,  WNDW_IRGHT, WNDW_RGHT, WNDW_CNTR, KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, TD(TD_LOWER_ESC), KC_ENT, KC_TAB, DF(BASE), KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    [HIGH] = LAYOUT_4x12(
        KC_DEL, KC_NO, DISP_DIM, DISP_BRI, KC_NO, OS_DRKMD_TGL, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RESET,
        KC_GRV, KC_NO, KC_VOLD, KC_VOLU, KC_NO, KC_MUTE, DF(HIGH), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DEBUG,
        KC_LSFT, KC_MRWD, MAC_MSTP, KC_MPLY, KC_MFFD, TGL_LYT, KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, DF(BASE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHEST] = LAYOUT_4x12(
        KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_GRV, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), TGL_HIGHEST, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, DF(HIGHEST), KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
    [HIGHEST_ALT] = LAYOUT_4x12(
        KC_DEL, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_GRV, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), TGL_HIGHEST, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, DF(HIGHEST_ALT), KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
	[OS] = LAYOUT_4x12(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OS_SCRN_SHT_OPT, OS_SPTLGHT, OS_LNCHPD, OS_SIRI, OS_SDBR, CMD_TAB_QUIT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OS_FLLSCRN, OS_PRV_SPC, OS_DSKTP, OS_MSN_CNTRL, OS_NXT_SPC, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OS_DOCK, CMD_TAB_PRV, PRV_APP, OS_EXPOSE, CMD_TAB_NXT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, DF(BASE), KC_ENT, OS_TRM_VSR, OS_LNCHR, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

