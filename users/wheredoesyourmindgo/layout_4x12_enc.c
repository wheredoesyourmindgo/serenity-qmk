#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_4x12_enc(
        KC_DEL, KC_F, KC_L, KC_H, KC_K, KC_Z, KC_G, KC_P, KC_O, KC_U, KC_EQL, KC_BSPC,
        KC_GRV, KC_S, KC_R, KC_N, KC_T, KC_M, KC_Y, KC_C, KC_E, KC_I, KC_A, KC_MINS,
        KC_LSFT, KC_X, KC_J, KC_B, KC_D, KC_V, KC_QUOT, KC_W, KC_Q, KC_COMM, KC_DOT, KC_RSFT,
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_ESC), LT(LOW,KC_ENT), ENC_BTN, LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    ),
    [BASE_QWRTY] = LAYOUT_4x12_enc(
        KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_MINS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_RSFT,
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_ESC), LT(LOW,KC_ENT), ENC_BTN, LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), LT(HIGHEST, KC_SLSH), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
	[LOWER] = LAYOUT_4x12_enc(
        KC_DEL , KC_1 , KC_2 , KC_3 , KC_4, KC_5, KC_6  , KC_7   , KC_8 , KC_9, KC_0, TRY_BSPACE_WORD,
        KC_GRV, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, OSL(HIGHER), KC_DOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_MINS,
        KC_LSFT, LT(LOWER_ALT,TGL_LOWER), OSM(MOD_RALT), KC_NO, KC_NO, DF(LOWER), KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, CAPS_SENTENCE,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI,  DF(BASE), KC_ENT, ENC_BTN, KC_TAB, LT(HIGHER, KC_SPC),  KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[LOWER_ALT] = LAYOUT_4x12_enc(
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ZOOM_RESET_APP, KC_TRNS, ZOOM_IN_APP, ZOOM_OUT_APP, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OS_BCK, OS_FWD_FLDR, OS_BCK_FLDR, OS_FWD, KC_TRNS,
        KC_TRNS,  LT(LOWER,TGL_LOWER), KC_TRNS, KC_TRNS, KC_TRNS, DF(LOWER_ALT), ZOOM_RESET, KC_TRNS, ZOOM_IN, ZOOM_OUT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(BASE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[LOW] = LAYOUT_4x12_enc(
        KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,              KC_CIRC,   KC_AMPR, KC_LPRN,  KC_RPRN, KC_ASTR, KC_BSPC,
        KC_TILD, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, OSL(HIGH),  KC_PIPE,   KC_LCBR, KC_LT, KC_GT, KC_RCBR, KC_UNDS,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO, DF(LOW),           KC_BSLASH, KC_SLSH, KC_LBRC,  KC_RBRC, KC_QUES, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, DF(BASE), ENC_BTN, KC_TAB, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [LOWEST] = LAYOUT_4x12_enc(
        KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LOCK, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, KC_BSPC,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN5, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO, DF(LOWEST), KC_NO, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        DF(BASE), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, KC_ENT, ENC_BTN, KC_TAB, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHER] = LAYOUT_4x12_enc(
        LALT(KC_DEL), OS_PRVS_APP_WNDW, OS_PRV_TAB, OS_NXT_TAB, OS_NXT_APP_WNDW, TD(TD_TGL_SEL), KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, KC_BSPC,
        TD(TD_MULTI_RSTR), TLNG_ILFT, TLNG_LFT, TLNG_RGHT, TLNG_IRGHT, TD(TD_MULTI_MAX), OSL(LOWER), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_CAPS, UNDO, CUT, COPY, PASTE, REDO, DF(HIGHER), KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, LT(LOWER, KC_ESC), KC_ENT, ENC_BTN, KC_TAB, DF(BASE), KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    [HIGH] = LAYOUT_4x12_enc(
        KC_DEL, KC_NO, DISP_DIM, DISP_BRI, OS_DRKMD_TGL, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RESET,
        KC_NO, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO, OSL(LOW), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DEBUG,
        KC_LSFT, KC_NO, KC_MRWD, KC_MFFD, KC_MPLY, TGL_LYT, DF(HIGH), KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, ENC_BTN, DF(BASE), KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHEST] = LAYOUT_4x12_enc(
        KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, DF(HIGHEST), KC_NO, KC_NO, OSM(MOD_RALT), LT(HIGHEST_ALT,TGL_HIGHEST), KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, ENC_BTN, KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
    [HIGHEST_ALT] = LAYOUT_4x12_enc(
        KC_DEL, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_NO, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DF(HIGHEST_ALT), KC_NO, KC_NO, OSM(MOD_RALT), LT(HIGHEST,TGL_HIGHEST), KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, ENC_BTN, KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
	[OS] = LAYOUT_4x12_enc(
        KC_NO, KC_NO, KC_NO, OS_TRM_VSR, OS_LNCHR, KC_NO, OS_SCRN_SHT_OPT, OS_SPTLGHT, OS_LNCHPD, OS_SIRI, OS_SDBR, KC_NO,
        KC_NO, PRV_APP, CMD_TAB_PRV, CMD_TAB_NXT, OS_EXPOSE, OS_FLLSCRN, KC_NO, OS_MSN_CNTRL, OS_PRV_SPC, OS_NXT_SPC, OS_DSKTP, KC_NO,
        KC_NO, OS_DOCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ENC_BTN, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO
    )
};

