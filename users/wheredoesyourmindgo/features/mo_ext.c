#include "wheredoesyourmindgo.h" // Include your keymap header file
#include "mo_ext.h" // Include your keymap header file

// Define the tapping term if not already defined
#ifndef MO_EXT_TAPPING_TERM
#define MO_EXT_TAPPING_TERM 300
#endif

// Variables to manage tap and hold states
static uint16_t custom_l_key_timer;
static uint16_t custom_r_key_timer;
static bool custom_l_key_active = false;
static bool custom_r_key_active = false;

bool process_mo_ext(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(SYMBL):
            if (record->event.pressed) {
                if (custom_l_key_active && timer_elapsed(custom_l_key_timer) < MO_EXT_TAPPING_TERM) {
                    // Second tap detected within the tapping term
                    layer_on(BASE_L); // Activate Base Left layer
                    return false;
                } else {
                    // First tap
                    custom_l_key_active = true;
                    custom_l_key_timer = timer_read();
                }
            } else {
                if (IS_LAYER_ON(BASE_L)) {
                    layer_off(BASE_L);
                }
            }
            return true;
        case MO(NUMNAV):
            if (record->event.pressed) {
                if (custom_r_key_active && timer_elapsed(custom_r_key_timer) < MO_EXT_TAPPING_TERM) {
                    // Second tap detected within the tapping term
                    layer_on(BASE_R); // Activate Base Right layer
                    return false;
                } else {
                    // First tap
                    custom_r_key_active = true;
                    custom_r_key_timer = timer_read();
                }
            } else {
                if (IS_LAYER_ON(BASE_R)) {
                    layer_off(BASE_R);
                }
            }
            return true;
        default:
            return true; // Process all other keycodes normally
    }
}
