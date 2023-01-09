
#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ortho_2x2u(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_EQL, KC_BSLS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_Q, KC_L, KC_C, KC_P, KC_B, KC_LBRC, KC_RBRC, KC_J, KC_F, KC_O, KC_U, KC_SCLN, KC_BSPC,
        LT(MOUSE, KC_MINS), KC_M, KC_R, KC_S, KC_T, KC_G, KC_HOME, KC_PGUP, KC_Y, KC_N, KC_E, KC_I, KC_A, KC_QUOT,
        KC_LSFT, KC_V, KC_X, KC_W, KC_D, KC_Z, KC_END, KC_PGDN, KC_K, KC_H, KC_SLSH, KC_COMM, KC_DOT, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_LCTL, KC_LALT, KC_LGUI, LT(NUMNAV,KC_ESC), LT(SYMBL,KC_ENT), LT(HRDWR,KC_SPC), LT(AUX,KC_TAB), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(FUNCXTR,KC_RIGHT)
    ),
    [QWRTY] = LAYOUT_ortho_2x2u(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_EQL, KC_BSLS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        OS_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, OS_BSPC,
        LT(MOUSE, KC_MINS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_HOME, KC_PGUP, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_END, KC_PGDN, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_LCTL, KC_LALT, KC_LGUI, LT(NUMNAV,KC_ESC), LT(SYMBL,KC_ENT), LT(HRDWR,KC_SPC), LT(AUX,KC_TAB), LT(FUNCXTR, KC_SLSH), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
	[NUMNAV] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL , KC_1 , KC_2 , KC_3 , KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8 , KC_9, KC_0, KC_BSPC,
        LT(MOUSE, KC_MINS), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, KC_NO, KC_NO, TD(TD_DOTEQL), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, UNDO, CUT, COPY, PASTE, REDO, KC_NO, KC_NO, TD(TD_PEMDAS), KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_LCTL, KC_LALT, KC_LGUI, KC_ESC, LT(SYMBL,KC_ENT), KC_SPC, LT(AUX,KC_TAB), KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
	[SYMBL] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_NO, KC_NO, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        LT(MOUSE, KC_MINS), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, KC_NO, KC_NO, KC_GRV, KC_BSLS, KC_EQL,  KC_LCBR, KC_RCBR, KC_QUOT,
        KC_LSFT, KC_LT, KC_GT, KC_DQUO, KC_COLN, KC_PLUS, KC_NO, KC_NO, KC_TILD, KC_PIPE, KC_PLUS, KC_LBRC, KC_RBRC, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_NO, KC_NO, KC_NO, LT(NUMNAV,KC_ESC), KC_ENT, KC_SPC, KC_TAB, KC_NO,  XOSM_RALT, KC_NO, KC_NO
    ),
    [MOUSE] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        OS_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, OS_BSPC,
        KC_MINS, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, LLOCK, KC_NO, KC_NO, KC_LOCK, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_QUOT,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, SHAKE_MOUSE, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, KC_SPC, KC_TAB, KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
	[AUX] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, OS_PRV_TAB, OS_PRV_APP_WNDW, OS_NXT_APP_WNDW, OS_NXT_TAB, TD(TD_TGL_SEL), KC_NO, KC_NO, KC_APP, KC_PSCR, KC_SCRL, KC_PAUS, KC_INS, KC_BSPC,
        KC_MINUS, KC_NO, TLNG_LFT, TLNG_RGHT, TD(TD_MULTI_RSTR), TD(TD_MULTI_MAX), KC_NO, KC_NO, LLOCK, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_QUOT,
        KC_LSFT, UNDO, CUT, COPY, PASTE, REDO, KC_NO, KC_NO, TGL_LYT, KC_CAPS, KC_NO, KC_NO, KC_NO, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_NO, XOSM_RALT, KC_NO, LT(NUMNAV,KC_ESC), LT(SYMBL,KC_ENT), KC_SPC, KC_TAB, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    [HRDWR] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        OS_DEL, KC_NO, DISP_DIM, DISP_BRI, OS_DRKMD_TGL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, QK_BOOT, KC_BSPC,
        KC_MINS, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO, KC_NO, KC_NO, LLOCK, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_QUOT,
        KC_LSFT, KC_NO, KC_MRWD, KC_MFFD, KC_MPLY, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_NO, XOSM_RALT, KC_NO, KC_ESC, KC_ENT, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[FUNC] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        OS_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, OS_BSPC,
        KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, LLOCK, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_QUOT,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_RCTL, XOSM_RALT, KC_RGUI, KC_ESC, KC_ENT, KC_SPC, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO
    ),
	[FUNCXTR] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        OS_DEL, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OS_BSPC,
        KC_MINS, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO, KC_NO, LLOCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT,
        LT(FUNC,KC_MUTE), KC_RCTL, XOSM_RALT, KC_RGUI, KC_ESC, KC_ENT, KC_SPC, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO
    ),
	[OS] = LAYOUT_ortho_2x2u(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        OS_DEL, KC_NO, KC_NO, OS_TRM_VSR, KC_NO, KC_NO, KC_NO, KC_NO, OS_SCRN_SHT_OPT, OS_LNCHPD, OS_SPTLGHT, OS_SIRI, OS_SDBR, OS_BSPC,
        KC_NO, OS_DSKTP, OS_PRV_SPC, OS_NXT_SPC, OS_MSN_CNTRL, OS_FLLSCRN, KC_NO, KC_NO, OS_DOCK, OS_EXPOSE, CMD_TAB_PRV, CMD_TAB_NXT, PRV_APP,  KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LGUI(KC_Q), LGUI(KC_H), KC_NO, KC_RSFT,
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    )
};
