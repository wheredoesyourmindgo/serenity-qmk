
#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_boardwalk_hs(
    #if defined COLEMAK_DH_RING
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_K, KC_Y, KC_C, KC_W, KC_P, KC_LBRC, KC_RBRC, KC_J, KC_L, KC_U, KC_SCLN, KC_Z, KC_BSPC,
        KC_QUOT, KC_R, KC_I, KC_S, KC_T, KC_G, KC_HOME, KC_PGUP,  KC_M, KC_N, KC_E, KC_A, KC_O, KC_MINS,
        TD(TD_CAPS_WORD), KC_X, KC_Q, KC_F, KC_D, KC_B, KC_END, KC_PGDN, KC_V, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    #elif defined COLEMAK_DH_OA
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_LBRC, KC_RBRC, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        KC_MINS, KC_O, KC_R, KC_S, KC_T, KC_G, KC_HOME, KC_PGUP,  KC_M, KC_N, KC_E, KC_I, KC_A, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_END, KC_PGDN, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    #else
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_LBRC, KC_RBRC, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        KC_MINS, KC_A, KC_R, KC_S, KC_T, KC_G, KC_HOME, KC_PGUP,  KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_END, KC_PGDN, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), LT(HIGHEST,KC_RIGHT)
    #endif
    ),
    [BASE_QWRTY] = LAYOUT_boardwalk_hs(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
        KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC,  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_MINS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_HOME, KC_PGUP,  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_V, KC_END, KC_PGDN, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, TD(TD_CAPS_SENTENCE),
        TD(TD_OOPSY), KC_LCTL, KC_LALT, KC_LGUI, TD(TD_LOWER_ESC), TD(TD_LOW_ENT), LT(HIGH,KC_TAB), LT(HIGHER,KC_SPC), LT(HIGHEST, KC_SLSH), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
	[LOWER] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL , KC_1 , KC_2 , KC_3 , KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8 , KC_9, KC_0, TRY_BSPACE_WORD,
        KC_MINS, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, OSL(HIGHER), KC_NO, KC_NO, KC_DOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, LT(LOWER_ALT,TGL_LOWER), OSM(MOD_RALT), KC_NO, VOID, DF(LOWER), KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, RSFT_T(KC_CAPS),
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI,  DF(BASE), KC_ENT, KC_TAB, LT(OS, KC_SPC),  KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[LOWER_ALT] = LAYOUT_boardwalk_hs(
        KC_TRNS  , KC_TRNS        , KC_TRNS        , KC_TRNS        , KC_TRNS        , KC_TRNS    ,         KC_TRNS, KC_TRNS, KC_TRNS         , KC_TRNS  , KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ZOOM_RESET_APP, KC_TRNS, ZOOM_IN_APP, ZOOM_OUT_APP, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OS_BCK, OS_FWD_FLDR, OS_BCK_FLDR, OS_FWD, KC_TRNS,
        KC_TRNS, LT(LOWER,TGL_LOWER), KC_TRNS, KC_TRNS, KC_TRNS, DF(LOWER_ALT), KC_TRNS, KC_TRNS, ZOOM_RESET, KC_TRNS, ZOOM_IN, ZOOM_OUT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(BASE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[LOW] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_NO, KC_NO, KC_CIRC, KC_AMPR, XASTR, XLPRN, XRPRN, KC_BSPC,
        KC_MINS, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, OSL(HIGH), KC_NO, KC_NO, KC_GRV , KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_QUOT,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, VOID, DF(LOW), KC_NO, KC_NO, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, DF(BASE), KC_TAB, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [LOWEST] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LOCK, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, KC_BSPC,
        KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN5, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_LSFT, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO, DF(LOWEST), KC_NO, KC_NO, KC_NO, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_RSFT,
        DF(BASE), XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, KC_ENT, KC_TAB, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHER] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LALT(KC_DEL), OS_PRV_TAB, OS_PRVS_APP_WNDW, OS_NXT_APP_WNDW, OS_NXT_TAB, TD(TD_TGL_SEL), KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, KC_BSPC,
        TD(TD_MULTI_RSTR),  TLNG_LFT, TLNG_ILFT,  TLNG_IRGHT, TLNG_RGHT, TD(TD_MULTI_MAX), KC_NO, KC_NO, OSL(LOWER), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        LSFT_T(KC_CAPS), UNDO, CUT, COPY, PASTE, REDO, KC_NO, KC_NO, DF(HIGHER), VOID, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, LT(OS, KC_ESC), KC_ENT, KC_TAB, DF(BASE), KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    [HIGH] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        KC_DEL, KC_NO, DISP_DIM, DISP_BRI, KC_NO, OS_DRKMD_TGL, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RESET,
        KC_MINS, KC_NO, KC_VOLD, KC_VOLU, KC_NO, KC_MUTE, KC_NO, KC_NO, OSL(LOW), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DEBUG,
        KC_LSFT, KC_MRWD, MAC_MSTP, KC_MPLY, KC_MFFD, TGL_LYT, KC_NO, KC_NO, DF(HIGH), VOID, KC_NO, OSM(MOD_RALT), KC_NO, KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, DF(BASE), KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[HIGHEST] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_MINS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NO, KC_NO, DF(HIGHEST), KC_NO, KC_NO, OSM(MOD_RALT), LT(HIGHEST_ALT,TGL_HIGHEST), KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
    [HIGHEST_ALT] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,      KC_NO, KC_NO , KC_NO, KC_NO , KC_NO, KC_NO,
        KC_DEL, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_MINS, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DF(HIGHEST_ALT), KC_NO, KC_NO, OSM(MOD_RALT), LT(HIGHEST,TGL_HIGHEST), KC_RSFT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_ENT, KC_TAB, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, DF(BASE)
    ),
	[OS] = LAYOUT_boardwalk_hs(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, OS_TRM_VSR, OS_LNCHR, KC_NO, OS_SCRN_SHT_OPT, KC_NO, KC_NO, OS_SPTLGHT, OS_LNCHPD, OS_SIRI, OS_SDBR, KC_NO,
        PRV_APP, CMD_TAB_PRV, OS_EXPOSE, OS_MSN_CNTRL, CMD_TAB_NXT, OS_FLLSCRN, KC_NO, KC_NO, OS_DSKTP, OS_PRV_SPC, OS_SPC1, OS_LAST_SPC, OS_NXT_SPC, KC_NO,
        KC_NO, OS_DOCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO
    )
};

