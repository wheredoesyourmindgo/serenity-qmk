// Tap / long-press keys: LT(0, kc) keys whose tap and hold each send a shortcut.
// The keycodes are defined in shortcuts.h.
#include "serenity.h"

// On press, send `tap_keycode` if tapped or `hold_keycode` if held
static bool tap_or_hold(keyrecord_t *record, uint16_t tap_keycode, uint16_t hold_keycode) {
    if (record->event.pressed) {
        tap_code16(record->tap.count > 0 ? tap_keycode : hold_keycode);
    }
    return false; // Skip default handling.
}

// Press a screenshot shortcut, then Space to switch it to window capture
static void screenshot_window(uint16_t shortcut) {
    tap_code16(shortcut);
    wait_ms(100); // Give macOS time to show the screenshot cursor
    tap_code(KC_SPC);
}

bool process_long_press_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DOT_LP: // Num/Nav: tap for a decimal point, hold for a thousands separator
            // Shift is ignored, so this key never types > or <
            if (record->event.pressed) {
                const uint8_t shift = get_mods() & MOD_MASK_SHIFT;
                del_mods(shift);
                tap_code16(record->tap.count > 0 ? KC_DOT : KC_COMM);
                add_mods(shift);
                send_keyboard_report();
            }
            return false;

        // Window management (Rectangle)
        case WNDW_MAX_LP:
            return tap_or_hold(record, WNDW_MAX, WNDW_RSTR);
        case WNDW_CNTR_LP:
            return tap_or_hold(record, WNDW_CNTR, WNDW_LWP);
        case WNDW_LFT_LP:
            return tap_or_hold(record, WNDW_LFT_HLF, WNDW_LFT_FILL);
        case WNDW_RGHT_LP:
            return tap_or_hold(record, WNDW_RGHT_HLF, WNDW_RGHT_FILL);
        case WNDW_VRT_MAX_LP:
            return tap_or_hold(record, WNDW_ALMST_MAX, WNDW_VRT_MAX);

        // Screenshots: tap saves to file, hold copies to clipboard
        case OS_SCRN_SHT_LP:
            return tap_or_hold(record, OS_SCRN_SHT, OS_SCRN_SHT_CLP);
        case OS_SCRN_SHT_SLCT_LP:
            return tap_or_hold(record, OS_SCRN_SHT_SLCT, OS_SCRN_SHT_CLP_SLCT);
        case OS_SCRN_SHT_WNDW_LP:
            if (record->event.pressed) {
                screenshot_window(record->tap.count > 0 ? OS_SCRN_SHT_SLCT : OS_SCRN_SHT_CLP_SLCT);
            }
            return false;
    }
    return true;
}
