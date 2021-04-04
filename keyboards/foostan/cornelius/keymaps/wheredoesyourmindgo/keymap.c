#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        LT(OS,KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_LCTL), TD(TD_LALT), TD(TD_LGUI), MO(LOWEST), MO(LOWER), LT(LOW,KC_SPC), LT(HIGH,KC_ENT), MO(HIGHER), MO(HIGHEST), TD(TD_RGUI), TD(TD_RALT), TD(TD_RCTL)
    ),
    [BASE_HRM] = LAYOUT(
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        LT(OS,KC_ESC), LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O), KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, ALGR_T(KC_X), KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, ALGR_T(KC_DOT), KC_SLSH, TD(TD_CAPS_SENTENCE),
        TD(TD_LCTL), TD(TD_LALT), TD(TD_LGUI), MO(LOWEST), MO(LOWER), LT(LOW,KC_SPC), LT(HIGH,KC_ENT), MO(HIGHER_HRM), MO(HIGHEST), TD(TD_RGUI), TD(TD_RALT), TD(TD_RCTL)
    ),
    [SFT_BASE] = LAYOUT(
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        LT(OS,KC_ESC),KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        TD(TD_CAPS_WORD), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, TD(TD_CAPS_SENTENCE),
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_SPC, KC_ENT, KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
    // Having MO(HIGHER) allows quick toggle select when arrowing with Lower layer
	[LOWER] = LAYOUT(
        KC_DEL , KC_1         , KC_2         , KC_3         , KC_4         , KC_5     ,         KC_6          , KC_7   , KC_8 , KC_9, KC_0, LALT(KC_BSPC),
        KC_ESC , XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOWER),         KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_GRV,
        KC_NO  , KC_NO        , OSM(MOD_RALT)      , KC_NO        , KC_NO        , KC_NO    ,          KC_NO  , KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT        , DF(BASE)     , KC_SPC   , KC_ENT, MO(HIGHER),  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[LOW] = LAYOUT(
        KC_DEL, KC_EXLM      , KC_AT        , KC_HASH      , KC_DLR       , KC_PERC ,                  KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_ASTR, KC_BSPC,
        KC_ESC, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOW),                  KC_MINS, KC_EQL , KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        KC_NO, KC_NO        , OSM(MOD_RALT), KC_NO        , KC_NO        , KC_NO   ,                  KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,        KC_NO        , DF(BASE), KC_NO, KC_NO,  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
    [LOWEST] = LAYOUT(
        KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN3, KC_BTN2, KC_NO, LGUI(KC_BSPC),
        KC_NO, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, DF(LOWEST), KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
        KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_NO,
        TD(TD_SFT_LCTL), TD(TD_SFT_LALT), TD(TD_SFT_LGUI), DF(BASE), KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[HIGHER] = LAYOUT(
        LALT(KC_DEL), KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, TD(TD_TGL_SEL), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_ESC, TO(BASE_HRM), KC_CAPS, KC_LEAD, OSHR, KC_APP, DF(HIGHER), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_NO, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), SGUI(KC_Z), KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, MO(LOWER), KC_SPC, KC_ENT, DF(BASE), KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[HIGHER_HRM] = LAYOUT(
        LALT(KC_DEL), KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, TD(TD_TGL_SEL), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_ESC, TO(BASE), KC_CAPS, KC_LEAD, OSHR, KC_APP, DF(HIGHER_HRM), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_NO, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), SGUI(KC_Z), KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_SPC, KC_ENT, DF(BASE_HRM), KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
    [HIGH] = LAYOUT(
        KC_DEL,  KC_NO, KC_NO , KC_NO,   KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   RESET,
        OOPS, KC_MUTE, KC_VOLD, KC_VOLU, VOL_JUP,   KC_NO,   DF(HIGHEST),   XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL,     DEBUG,
        KC_NO ,  MAC_MSTP, KC_MRWD,  KC_MFFD,  KC_MPLY,  KC_NO,  KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,  KC_NO, DF(BASE), KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    ),
	[HIGHEST] = LAYOUT(
        LCTL(KC_K), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
        KC_NO, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, DF(HIGH), XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_NO,
        KC_NO, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, KC_NO, KC_NO, OSM(MOD_RALT), KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, DF(BASE), TD(TD_SFT_RGUI), TD(TD_SFT_RALT), TD(TD_SFT_RCTL)
    ),
	[OS] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    OS_SCRN_SHT_OPT,  OS_SPTLGHT,     OS_LNCHPD,          OS_SIRI,            OS_SDBR,        DF(WNDW),
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    PRV_APP,       OS_PRV_SPC,     CMD_TAB_PRV,        CMD_TAB_NXT,        OS_NXT_SPC,     OS_FLLSRN,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    OS_DSKTP,         OS_MSN_CNTRL,   OS_PRVS_APP_WNDW,   OS_NXT_APP_WNDW,    OS_APP_WNDWS,   KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OS_APP1,  OS_APP2,           KC_NO,          KC_NO,              KC_NO,              KC_NO,          KC_NO
    ),
	[WNDW] = LAYOUT(
        KC_NO   , WNDW_RSTR, LCA(KC_U)   ,               WNDW_TOP_HLF , LCA(KC_I), KC_NO, KC_NO, KC_NO , WNDW_SMLLR , WNDW_LRGR, KC_NO, KC_NO,
        DF(BASE), WNDW_CNTR, WNDW_LFT_HLF,               WNDW_CNTR_HLF, WNDW_RGHT_HLF, KC_NO, WNDW_MAX , WNDW_MV_LFT, WNDW_MV_DWN, WNDW_MV_UP, WNDW_MV_RGHT, KC_NO,
        KC_NO   , KC_NO    , LCA(KC_J)   ,               WNDW_BTTM_HLF, LCA(KC_K),  KC_NO    ,LCA(KC_F), LCA(KC_D)  ,LCA(KC_E)   , LCA(KC_T), LCA(KC_G),     KC_NO,
        KC_NO, KC_NO , KC_NO , KC_NO, KC_NO, WNDW_VRT_MAX , WNDW_ALMST_MAX, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

