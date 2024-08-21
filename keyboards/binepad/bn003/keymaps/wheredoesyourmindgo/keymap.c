#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"
/*
0x4287 product_id conflicts with BNR1, so pid 0x4286 is specifed in info.json
*/

/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LP_TAB:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(LGUI(KC_T));
                }
            } else {
                if (record->event.pressed) {
                    tap_code16(LGUI(KC_W));
                }
            }
            return false;  // Skip default handling.
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    #if defined BN003_USB_LEFT
        OS_NXT_TAB,
        LP_TAB,
        OS_PRV_TAB
    #else
        OS_PRV_TAB,
        LP_TAB,
        OS_NXT_TAB
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
