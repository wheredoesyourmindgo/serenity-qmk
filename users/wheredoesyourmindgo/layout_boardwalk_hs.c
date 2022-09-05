
#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_boardwalk_hs(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_SLSH, KC_BSLS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_Q, KC_L, KC_C, KC_P, KC_B, KC_LBRC, KC_RBRC, KC_J, KC_F, KC_O, KC_U, KC_BSLS, KC_BSPC,
        LT(LOWEST, KC_MINS), KC_Y, KC_R, KC_S, KC_T, KC_G, KC_HOME, KC_PGUP, KC_M, KC_N, KC_E, KC_I, KC_A, KC_QUOT,
        KC_LSFT, KC_V, KC_X, KC_W, KC_D, KC_Z, KC_END, KC_PGDN, KC_K, KC_H, KC_SLSH, KC_COMM, KC_DOT, KC_RSFT,
        TD(TD_OOPS), KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_ESC), LT(LOW,KC_ENT), LT(HIGH,KC_SPC), LT(HIGHER,KC_TAB), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    ),
    [QWRTY] = LAYOUT_boardwalk_hs(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_SLSH, KC_BSLS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        OS_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, OS_BSPC,
        LT(LOWEST, KC_MINS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_HOME, KC_PGUP, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_END, KC_PGDN, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_RSFT,
        TD(TD_OOPS), KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_ESC), LT(LOW,KC_ENT), LT(HIGH,KC_SPC), LT(HIGHER,KC_TAB), LT(HIGHEST, KC_SLSH), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
	[LOWER] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL , KC_1 , KC_2 , KC_3 , KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8 , KC_9, KC_0, KC_BSPC,
        LT(LOWEST, KC_MINS), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, KC_NO, KC_NO, KC_DOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, UNDO, CUT, COPY, PASTE, REDO, KC_NO, KC_NO, TD(TD_PEMDAS), KC_HOME, KC_PGDN, KC_PGUP, KC_END, CAPS_SENTENCE,
        TD(TD_OOPS), KC_LCTL, KC_LALT, KC_LGUI, KC_ESC, KC_ENT, KC_SPC, LT(HIGHER,KC_TAB), KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
	[LOW] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_NO, KC_NO,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        LT(LOWEST, KC_MINS), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, KC_NO, KC_NO, KC_GRV, KC_BSLS, KC_EQL,  KC_LCBR, KC_RCBR, KC_QUOT,
        KC_LSFT, KC_LT, KC_GT, KC_DQUO, KC_COLN, KC_PLUS, KC_NO, KC_NO,                      KC_TILD, KC_PIPE, KC_PLUS, KC_LBRC, KC_RBRC, KC_CAPS,
        TD(TD_OOPS), KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, KC_SPC, KC_TAB, KC_NO,  XOSM_RALT, KC_NO, KC_NO
    ),
    [LOWEST] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        OS_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, OS_BSPC,
        KC_MINS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, LLOCK, KC_NO, KC_NO, KC_LOCK, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_QUOT,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, SHAKE_MOUSE, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        TD(TD_OOPS), KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, KC_SPC, KC_TAB, KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
	[HIGHER] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, OS_BCK_FWD, OS_PRV_TAB, OS_NXT_TAB, OS_NXT_APP_WNDW, TD(TD_TGL_SEL), KC_NO, KC_NO, KC_APP, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, KC_BSPC,
        TD(TD_MULTI_RSTR), TLNG_LFT, TLNG_ILFT, TLNG_IRGHT, TLNG_RGHT, TD(TD_MULTI_MAX), KC_NO, KC_NO, LLOCK, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_QUOT,
        CAPS_SENTENCE, UNDO, CUT, COPY, PASTE, REDO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT,
        TD(TD_OOPS), KC_NO, XOSM_RALT, KC_NO, LT(LOWER, KC_ESC), KC_ENT, KC_SPC, KC_TAB, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    [HIGH] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        OS_DEL, KC_NO, DISP_DIM, DISP_BRI, OS_DRKMD_TGL, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSPC,
        KC_MINS, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO, KC_NO, KC_NO, LLOCK, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_QUOT,
        KC_CAPS, KC_NO, KC_MRWD, KC_MFFD, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TGL_LYT, DEBUG, RESET, KC_RSFT,
        TD(TD_OOPS), KC_NO, XOSM_RALT, KC_NO, KC_ESC, KC_ENT, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHEST] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        OS_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_F22, KC_F23, KC_F24, KC_NO, OS_BSPC,
        KC_MINS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, LLOCK, KC_F19, KC_F20, KC_F21, KC_NO, KC_QUOT,
        KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NO, KC_NO, KC_NO, KC_F16, KC_F17, KC_F18, KC_NO, KC_RSFT,
        TD(TD_OOPS), KC_RCTL, XOSM_RALT, KC_RGUI, KC_ESC, KC_ENT, KC_SPC, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO
    ),
	[OS] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        OS_DEL, KC_NO, KC_NO, OS_TRM_VSR, OS_LNCHR, KC_NO, KC_NO, KC_NO, OS_SCRN_SHT_OPT, OS_SPTLGHT, OS_LNCHPD, OS_SIRI, OS_SDBR, OS_BSPC,
        KC_NO, OS_DSKTP, OS_PRV_SPC, OS_NXT_SPC, OS_MSN_CNTRL, OS_FLLSCRN, KC_NO, KC_NO, OS_DOCK, OS_EXPOSE, CMD_TAB_PRV, CMD_TAB_NXT, PRV_APP,  KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LGUI(KC_Q), LGUI(KC_H), KC_NO, KC_RSFT,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    )
};

