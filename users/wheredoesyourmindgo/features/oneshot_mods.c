#include "oneshot_mods.h"
#include "wheredoesyourmindgo.h"
#include "print.h"


void oneshot_mods_layer_state(layer_state_t state) {
    dprint("layer state changed\n");
    dprintf("Layer: %d\n", biton32(layer_state));
    switch (get_highest_layer(state)) {
        case BASE:
        case QWRTY:
        // AUX and HRDWR are required in order to use OSM with Function layer.
        case AUX:
        case HRDWR:
            dprint("preserving one shot mods (break'ing)\n");
            break;
        //  for any other layers
        default:
            // Cancel One Shot Mods (if active) is necessary when switching to layers OTHER than base layer. This will prevent an issue where the keyboard might get stuck in a layer.
            if (ONESHOT_MODS_ACTIVE) {
                dprint("clearing one shot mods\n");
                clear_oneshot_mods();
                send_keyboard_report();
            }
            break;
    }
}

// Variable to store the timer and state
static uint16_t lctrl_timer;
static uint16_t lalt_timer;
static uint16_t lgui_timer;
static uint16_t lsft_timer;
static uint16_t rctrl_timer;
static uint16_t ralt_timer;
static uint16_t rgui_timer;
static uint16_t rsft_timer;


bool process_oneshot_mods(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case XOSM_LSFT:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                lsft_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_LSFT));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(lsft_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_LSFT));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_LGUI:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                lgui_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_LGUI));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(lgui_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_LGUI));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_LALT:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                lalt_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_LALT));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(lalt_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_LALT));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_LCTL:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                lctrl_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_LCTL)); // Register left control
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(lctrl_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_LCTL));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_RSFT:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                rsft_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_RSFT));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(rsft_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_RSFT));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_RGUI:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                rgui_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_RGUI));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(rgui_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_RGUI));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_RALT:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                ralt_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_RALT));
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(ralt_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_RALT));
                    send_keyboard_report();
                }
            }
            return false;
        case XOSM_RCTL:
            if (record->event.pressed) {
                // Key has been pressed, start the timer
                rctrl_timer = timer_read();
                add_oneshot_mods(MOD_BIT(KC_RCTL)); // Register right control
                send_keyboard_report();
            } else {
                // Key has been released
                if (timer_elapsed(rctrl_timer) > OSM_TAPPING_TERM) {
                    // Key was released after the tapping term expired
                    del_oneshot_mods(MOD_BIT(KC_RCTL));
                    send_keyboard_report();
                }
            }
            return false;
        case KC_ESC:
            if (record->event.pressed) {
                // Cancel One Shot Mods (if active)
                if (ONESHOT_MODS_ACTIVE) {
                    clear_oneshot_mods();
                    send_keyboard_report();
                    // Only fire escape special mode is not active
                    return false;
                }
            }
            break;
        case LT(MOUSE, KC_ESC):
            dprintf("case LT(MOUSE, KC_ESC):\n");
            dprintf("Key pressed: 0x%04X, Layer: %d\n", keycode, biton32(layer_state));
            if (record->event.pressed) {
                dprint("record->event.pressed\n");
                dprintf("Key pressed: 0x%04X, Layer: %d\n", keycode, biton32(layer_state));
                // Only on tap (ie. Not during LT(NUMNAV)
                if (record->tap.count > 0) {
                    dprint("record->tap.count > 0\n");
                    dprintf("Key pressed: 0x%04X, Layer: %d\n", keycode, biton32(layer_state));
                    // Cancel One Shot Mods (if active)
                    if (ONESHOT_MODS_ACTIVE) {
                        dprint("clearing one shot mods\n");
                        clear_oneshot_mods();
                        send_keyboard_report();
                        // Only fire escape special mode is not active
                        return false;
                    }
                }
                // The following is handled by oneshot_mods_layer_state
                // else {
                //     // Cancel One Shot Mods (if active)
                //     if (ONESHOT_MODS_ACTIVE) {
                //         clear_oneshot_mods();
                //         send_keyboard_report();
                //         return true;
                //     }
                // }
            }
            break;
    }

    return true;
}
