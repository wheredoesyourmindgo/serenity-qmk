#include QMK_KEYBOARD_H
#include "serenity.h"

// Two builds share this keymap, written for the full bottom row (LAYOUT_ortho_2x2u):
//   serenity        open case: every key, with the arrow cluster like the other boards
//   serenity_hhkb   HHKB-style case: the two bottom 1.5u corners are blocked, so they're dropped
//                   (LAYOUT_ortho_hhkb), and with no room for the arrow cluster the bottom-right
//                   keys are plain Hardware and mods
#ifdef SERENITY_HHKB
// clang-format off
#    define LAYOUT_serenity( \
        k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, \
        k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, \
        k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, \
        k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, \
        k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411 \
    ) LAYOUT_ortho_hhkb( \
        k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, \
        k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, \
        k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, \
        k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, \
        k401, k402, k403, k404, k405, k406, k407, k408, k409, k410 \
    )
// clang-format on
#    define BR_HRDWR MO(HRDWR)
#    define BR_RGUI KC_RGUI
#    define BR_RALT KC_RALT
#    define BR_RCTL KC_RCTL // Blocked corner, dropped
#else
#    define LAYOUT_serenity LAYOUT_ortho_2x2u
#    define BR_HRDWR LT(HRDWR, KC_LEFT)
#    define BR_RGUI RGUI_T(KC_DOWN)
#    define BR_RALT RALT_T(KC_UP)
#    define BR_RCTL RCTL_T(KC_RIGHT)
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_serenity(
        KC_LCTL,           KC_1,    KC_2,    KC_3,     KC_4,       KC_5,   KC_EQL,         KC_BSLS, KC_6, KC_7,      KC_8,     KC_9,    KC_0,    KC_RCTL,
        KC_TAB,            KC_Q,    KC_Z,    KC_M,     KC_W,       KC_V,   KC_LBRC,        KC_RBRC, KC_J, KC_F,      KC_O,     KC_U,    KC_MINS, KC_BSPC,
        LT(MOUSE, KC_ESC), KC_R,    KC_N,    KC_T,     KC_S,       KC_G,   KC_HOME,        KC_PGUP, KC_Y, KC_H,      KC_E,     KC_A,    KC_I,    KC_SCLN,
        KC_LSFT,           KC_X,    KC_L,    KC_D,     KC_C,       KC_B,   KC_END,         KC_PGDN, KC_K, KC_P,      KC_QUOT,  KC_COMM, KC_DOT,  RSFT_T(KC_ENT),
        KC_LCTL,           KC_LALT, KC_LGUI, MO(ACTN), MO(NUMNAV), KC_SPC,                 KC_SPC,        MO(SYMBL), BR_HRDWR, BR_RGUI, BR_RALT, BR_RCTL
    ),
    [QWRTY] = LAYOUT_serenity(
        KC_LCTL,           KC_1,    KC_2,    KC_3,     KC_4,       KC_5,   KC_EQL,         KC_BSLS, KC_6, KC_7,      KC_8,     KC_9,    KC_0,    KC_RCTL,
        KC_TAB,            KC_Q,    KC_W,    KC_E,     KC_R,       KC_T,   KC_LBRC,        KC_RBRC, KC_Y, KC_U,      KC_I,     KC_O,    KC_P,    KC_BSPC,
        LT(MOUSE, KC_ESC), KC_A,    KC_S,    KC_D,     KC_F,       KC_G,   KC_HOME,        KC_PGUP, KC_H, KC_J,      KC_K,     KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,     KC_V,       KC_B,   KC_END,         KC_PGDN, KC_N, KC_M,      KC_COMM,  KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        KC_LCTL,           KC_LALT, KC_LGUI, MO(ACTN), MO(NUMNAV), KC_SPC,                 KC_SPC,        MO(SYMBL), BR_HRDWR, BR_RGUI, BR_RALT, BR_RCTL
    ),
    [NUMNAV] = LAYOUT_serenity(
        KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,  KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   SOSM_RC,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,        KC_NO,  KC_6,    KC_7,      KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_ESC,  SOSM_LC, SOSM_LA, SOSM_LG, SOSM_LS, QK_LLCK, KC_NO,        KC_NO,  SELWORD, KC_LEFT,   KC_DOWN, KC_UP,   KC_RGHT, NUM_DOT,
        KC_LSFT, UNDO,    CUT,     COPY,    PASTE,   REDO,    KC_NO,        KC_NO,  KC_CAPS, KC_HOME,   KC_PGDN, KC_PGUP, KC_END,  KC_ENT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   KC_NO,   KC_SPC,                KC_SPC,          MO(SYMBL), KC_NO,   SOSM_RG, SOSM_RA, SOSM_RC
    ),
    [SYMBL] = LAYOUT_serenity(
        SOSM_LC, KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,        KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_RCTL,
        KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,     KC_PERC, KC_NO,        KC_NO,  KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_ESC,  KC_LBRC, KC_RBRC, KC_EQL,  KC_SLSH,    KC_BSLS, KC_NO,        KC_NO,  QK_LLCK, SOSM_LS,  SOSM_LG, SOSM_LA, SOSM_LC, KC_SCLN,
        KC_LSFT, KC_LCBR, KC_RCBR, KC_PLUS, KC_QUES,    KC_PIPE, KC_NO,        KC_NO,  KC_COLN, KC_TILDE, KC_GRV,  KC_LABK, KC_RABK, KC_ENT,
        SOSM_LC, SOSM_LA, SOSM_LG, KC_NO,   MO(NUMNAV), KC_SPC,                KC_SPC,          KC_NO,    KC_NO,   KC_RGUI, KC_RALT, KC_RCTL
    ),
    [ACTN] = LAYOUT_serenity(
        KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,        KC_NO,  KC_NO,           KC_NO,        KC_NO,           KC_NO,           KC_NO,        SOSM_RC,
        KC_TAB,  KC_PSCR, KC_SCRL, KC_PAUS, KC_INS,     KC_APP,  KC_NO,        KC_NO,  WNDW_MAX_LP,     OS_PRV_TAB,   OS_PRV_APP_WNDW, OS_NXT_APP_WNDW, OS_NXT_TAB,   KC_BSPC,
        KC_ESC,  SOSM_LC, SOSM_LA, SOSM_LG, SOSM_LS,    QK_LLCK, KC_NO,        KC_NO,  WNDW_CNTR_LP,    WNDW_LFT_LP,  WNDW_SMLLR,      WNDW_LRGR,       WNDW_RGHT_LP, KC_SCLN,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,        KC_NO,  WNDW_VRT_MAX_LP, WNDW_PRV_SPC, KC_NO,           KC_NO,           WNDW_NXT_SPC, KC_ENT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   MO(NUMNAV), KC_SPC,                KC_SPC,                  MO(SYMBL),    MO(HRDWR),       SOSM_RG,         SOSM_RA,      SOSM_RC
    ),
    [HRDWR] = LAYOUT_serenity(
        SOSM_LC, KC_NO,       KC_NO,    KC_NO,    KC_NO,        KC_NO,        KC_NO,        UG_SPDU, UG_NEXT, UG_TOGG,   UG_HUEU,    UG_SATU,   UG_VALU,    KC_RCTL,
        KC_TAB,  KC_NO,       DISP_DIM, DISP_BRI, OS_DRKMD_TGL, KC_NO,        KC_NO,        KC_NO,   KC_NO,   KC_NO,     KC_NO,      KC_NO,     KC_NO,      KC_BSPC,
        KC_ESC,  OS_MIC_MUTE, KC_VOLD,  KC_VOLU,  KC_MUTE,      OS_DND,       KC_NO,        KC_NO,   QK_LLCK, SOSM_LS,   SOSM_LG,    SOSM_LA,   SOSM_LC,    KC_SCLN,
        KC_LSFT, KC_NO,       KC_MRWD,  KC_MFFD,  KC_MPLY,      KC_NO,        KC_NO,        KC_NO,   TGL_LYT, KC_NO,     DB_TOGG_LP, EE_CLR_LP, QK_BOOT_LP, KC_ENT,
        SOSM_LC, SOSM_LA,     SOSM_LG,  MO(ACTN), MO(NUMNAV),   KC_SPC,                     KC_SPC,           MO(SYMBL), KC_NO,      KC_RGUI,   KC_RALT,    KC_RCTL
    ),
    [FUNC] = LAYOUT_serenity(
        KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RCTL,
        KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_NO,        KC_NO,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC,
        KC_ESC,  SOSM_LC, SOSM_LA, SOSM_LG, SOSM_LS, KC_NO,  KC_NO,        KC_NO,  KC_NO,  SOSM_LS, SOSM_LG, SOSM_LA, SOSM_LC, KC_SCLN,
        KC_LSFT, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15, KC_NO,        KC_NO,  KC_F16, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_ENT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   KC_NO,   KC_SPC,               KC_SPC,         KC_NO,   KC_NO,   KC_RGUI, KC_RALT, KC_RCTL
    ),
    [OS] = LAYOUT_serenity(
        KC_LCTL, KC_NO,          KC_NO,               KC_NO,               KC_NO,           KC_NO,        KC_NO,        KC_NO,  KC_NO,           KC_NO,         KC_NO,       KC_NO,       KC_NO,          KC_RCTL,
        KC_TAB,  OS_FRC_QUIT,    OS_CLOSE,            OS_MIN,              OS_FLLSCRN,      OS_LOCK_SCRN, KC_NO,        KC_NO,  KC_NO,           OS_SPTLGHT_LP, OS_LNCHPD,   OS_SIRI,     OS_SDBR,        KC_BSPC,
        KC_ESC,  OS_DSKTP,       OS_PRV_SPC,          OS_NXT_SPC,          OS_MSN_CNTRL,    OS_STG_MNGR,  KC_NO,        KC_NO,  OS_DOCK,         OS_EXPOSE,     CMD_TAB_PRV, CMD_TAB_NXT, OS_PRV_APP,     KC_SCLN,
        KC_LSFT, OS_SCRN_SHT_LP, OS_SCRN_SHT_WNDW_LP, OS_SCRN_SHT_SLCT_LP, OS_SCRN_SHT_OPT, OS_STOP_REC,  KC_NO,        KC_NO,  KC_NO,           KC_NO,         LGUI(KC_Q),  LGUI(KC_H),  OS_HIDE_OTHERS, KC_ENT,
        KC_LCTL, KC_LALT,        KC_LGUI,             KC_NO,               KC_NO,           KC_SPC,                     KC_SPC,                  KC_NO,         KC_NO,       KC_RGUI,     KC_RALT,        KC_RCTL
    ),
    [MOUSE] = LAYOUT_serenity(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,  KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   SOSM_RC,
        KC_TAB,  KC_NO,   MS_ACL0, MS_ACL1, MS_ACL2, KC_NO,   KC_NO,        KC_NO,  KC_NO,       OS_BACK, MS_BTN3, KC_NO,   OS_FWD,  KC_BSPC,
        KC_ESC,  SOSM_LC, SOSM_LA, SOSM_LG, SOSM_LS, QK_LLCK, KC_NO,        KC_NO,  QK_LOCK,     MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_SCLN,
        KC_LSFT, UNDO,    CUT,     COPY,    PASTE,   REDO,    KC_NO,        KC_NO,  SHAKE_MOUSE, MS_WHLR, MS_WHLU, MS_WHLD, MS_WHLL, KC_ENT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,                KC_SPC,              MS_BTN1, MS_BTN2, SOSM_RG, SOSM_RA, SOSM_RC
    ),
};
// clang-format on
