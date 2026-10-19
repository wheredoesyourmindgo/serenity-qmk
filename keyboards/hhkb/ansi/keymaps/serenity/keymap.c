#include QMK_KEYBOARD_H
#include "serenity.h"

// This board has two extra layers instead of the full Serenity set. They reuse Serenity layers
// so the shared userspace code sees the right layer (BASE comes from serenity.h).
#define LOWER NUMNAV // Navigation, one-shot mods, editing
#define RAISE FUNC   // Function keys, media, bootloader

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT( // default layer
        KC_GRV,            KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,              KC_7, KC_8,    KC_9,    KC_0,    KC_LBRC,        KC_RBRC, KC_BSLS, KC_DEL,
        KC_TAB,            KC_Q,    KC_Z,    KC_M, KC_W, KC_V, KC_J,              KC_F, KC_O,    KC_U,    KC_MINS, KC_EQL,         KC_SLSH, KC_BSPC,
        LT(RAISE, KC_ESC), KC_R,    KC_N,    KC_T, KC_S, KC_G, KC_Y,              KC_H, KC_E,    KC_A,    KC_I,    KC_SCLN,        KC_ENT,
        KC_LSFT,           KC_X,    KC_L,    KC_D, KC_C, KC_B, KC_K,              KC_P, KC_QUOT, KC_COMM, KC_DOT,  RSFT_T(KC_ENT), KC_RCTL,
                           KC_LALT, KC_LGUI,                   LT(LOWER, KC_SPC),                                  KC_RGUI,        KC_RALT
    ),
    [LOWER] = LAYOUT(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   KC_TRNS, KC_BSPC,
        KC_TRNS, SOSM_LC, SOSM_LA, SOSM_LG, SOSM_LS, KC_TRNS, KC_PAST, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_PENT,
        KC_TRNS, UNDO,    CUT,     COPY,    PASTE,   REDO,    KC_CAPS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS, KC_TRNS
    ),
    [RAISE] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS, KC_TRNS
    )
};
// clang-format on
