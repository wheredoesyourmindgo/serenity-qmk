#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

#define BASE 0
#define LOWER 1
#define RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_60_ansi(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_TAB, KC_Q, KC_Z, KC_M, KC_W, KC_V, KC_J, KC_F, KC_O, KC_U, KC_MINS, KC_EQL, KC_SLSH, KC_BSLS,
        LT(RAISE,KC_ESC), KC_R, KC_N, KC_T, KC_S, KC_G, KC_Y, KC_H, KC_E, KC_A, KC_I, KC_SCLN, KC_ENT,
        KC_LSFT, KC_X, KC_L, KC_D, KC_C, KC_B, KC_K, KC_P, KC_QUOT, KC_COMM, KC_DOT, RSFT_T(KC_ENT),
        KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER, KC_SPC), KC_RGUI, KC_RALT, KC_RCTL, MO(RAISE)
    ),
    [LOWER] = LAYOUT_60_ansi(
        QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          _______,
        KC_MPRV,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_PGDN,          KC_MNXT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [RAISE] = LAYOUT_60_ansi(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RM_TOGG, _______, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, RM_NEXT, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDU, RM_SPDD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};
