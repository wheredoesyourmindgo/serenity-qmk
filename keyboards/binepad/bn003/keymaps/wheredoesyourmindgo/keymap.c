#include QMK_KEYBOARD_H
/*
0x4287 product_id conflicts with BNR1, so pid 0x4286 is specifed in info.json
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    #if defined BN003_USB_LEFT
        KC_F24,
        KC_F23,
        KC_F22
    #else
        KC_F22,
        KC_F23,
        KC_F24
    #endif
    ),
    [1] = LAYOUT(
        KC_NO,
        KC_NO,
        KC_NO
    ),
    [2] = LAYOUT(
        KC_NO,
        KC_NO,
        KC_NO
    )
};
