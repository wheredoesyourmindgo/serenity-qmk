#include "oneshot_mods.h"
#include "wheredoesyourmindgo.h"
#include "print.h"

// Helper function for handling oneshot mods
static bool handle_oneshot_mod(uint8_t mod_bit, uint16_t* timer, keyrecord_t* record) {
    if (record->event.pressed) {
        register_mods(mod_bit);
        *timer = timer_read();
        add_oneshot_mods(mod_bit);
        send_keyboard_report();
    } else {
        unregister_mods(mod_bit);
        if (timer_elapsed(*timer) > OSM_TAPPING_TERM) {
            del_oneshot_mods(mod_bit);
            send_keyboard_report();
        }
    }
    return false;
}

bool cancel_oneshot_mods_if_active(void) {
    if (ONESHOT_MODS_ACTIVE) {
        dprint("clearing one shot mods\n");
        clear_oneshot_mods();
        send_keyboard_report();
        return true;
    }
    return false;
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
            return handle_oneshot_mod(MOD_BIT(KC_LSFT), &lsft_timer, record);
        case XOSM_LGUI:
            return handle_oneshot_mod(MOD_BIT(KC_LGUI), &lgui_timer, record);
        case XOSM_LALT:
            return handle_oneshot_mod(MOD_BIT(KC_LALT), &lalt_timer, record);
        case XOSM_LCTL:
            return handle_oneshot_mod(MOD_BIT(KC_LCTL), &lctrl_timer, record);
        case XOSM_RSFT:
            return handle_oneshot_mod(MOD_BIT(KC_RSFT), &rsft_timer, record);
        case XOSM_RGUI:
            return handle_oneshot_mod(MOD_BIT(KC_RGUI), &rgui_timer, record);
        case XOSM_RALT:
            return handle_oneshot_mod(MOD_BIT(KC_RALT), &ralt_timer, record);
        case XOSM_RCTL:
            return handle_oneshot_mod(MOD_BIT(KC_RCTL), &rctrl_timer, record);
    }

    return true;
}
