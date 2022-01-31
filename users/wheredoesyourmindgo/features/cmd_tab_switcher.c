// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "cmd_tab_switcher.h"
#include "wheredoesyourmindgo.h"

bool is_cmd_tab_active = false;
bool is_cmd_tab_held = false;

uint16_t cmd_tab_timer = 0;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

void cancel_cmd_shift(void) {
    unregister_mods(MOD_BIT(KC_LGUI));
    if (MODS_LSFT) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    is_cmd_tab_active = false;
    cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
}

void cmd_tab_switcher_layer_state(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default: //  for any other layers, or the default layer
            // cancel cmd-tab switcher when switching back to base layer
            if (is_cmd_tab_active) {
                cancel_cmd_shift();
            }
            break;
    }
}

void cmd_tab_switcher_matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > cmd_tab_timer_timeout && !is_cmd_tab_held) {
            cancel_cmd_shift();
        }
    }
}

bool process_cmd_tab_switcher(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case OS_PRV_SPC:
        case OS_NXT_SPC:
            if (record->event.pressed) {
                is_cmd_tab_held = true;
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
            }
            break;
        case CMD_TAB_NXT:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_mods(MOD_BIT(KC_LGUI));
                } else {
                    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
                    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
                }
                is_cmd_tab_held = true;
                unregister_mods(MOD_BIT(KC_LSFT));
                // cmd_tab_timer = timer_read(); // Start the timer when the key is released, not pressed
                tap_code(KC_TAB);
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
                // unregister_code(KC_TAB);
            }
            break;
        // case CMD_TAB_HIDE:
        //     if (record->event.pressed) {
        //         if (is_cmd_tab_active) {
        //             cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
        //             cmd_tab_timer = timer_read();
        //             tap_code(KC_H);
        //             return false;
        //         }
        //     }
        //     break;
        case OS_EXPOSE:
            if (record->event.pressed) {
                if (is_cmd_tab_active) {
                    tap_code(KC_UP);
                    return false;
                }
            }
            break;
        case OS_DOCK:
            if (record->event.pressed) {
                // Hide app during cmd+tab
                if (is_cmd_tab_active) {
                    cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
                    cmd_tab_timer = timer_read();
                    tap_code(KC_H);
                    return false;
                }
            }
            break;
        case CMD_TAB_PRV:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                } else {
                    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
                    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
                }
                register_mods(MOD_BIT(KC_LSFT));
                tap_code(KC_TAB);
                is_cmd_tab_held = true;
                // cmd_tab_timer = timer_read();
            } else {
                cmd_tab_timer   = timer_read();
                is_cmd_tab_held = false;
                unregister_mods(MOD_BIT(KC_LSFT));
                // unregister_code(KC_TAB);
            }
            break;
    }

    return true;
}
