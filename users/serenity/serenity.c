// Serenity userspace: QMK hooks shared by every keymap.
//
// Other parts live in:
//   helpers.c         tap_code*_no_mod() and other small helpers
//   long_press.c      LT(0, kc) tap / long-press shortcut keys
//   tapping.c         per-key tap-hold settings
//   rotary_encoder.c  rotary encoder
//   features/         self-contained features (one-shot mods, cmd-tab switcher, ...)
#include "serenity.h"
#include "features/oneshot_mods.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"
#include "features/mash_arrows.h"
#include "features/mo_ext.h"
#include "process_layer_lock.h" // QMK core Layer Lock (QK_LLCK)

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Ignore Shift presses (e.g. for a double quote)
        case KC_LSFT:
        case KC_RSFT:
            return true;
        // Keycodes that continue Caps Word, with shift applied
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        // Keycodes that continue Caps Word, without shifting
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_QUOT:
            return true;
        default:
            return false; // Deactivate Caps Word
    }
}

// Escape first cancels one-shot mods, then a locked layer. Returns true if it cancelled something.
static bool escape_cancels_something(void) {
    if (cancel_oneshot_mods_if_active()) {
        return true;
    }
    const uint8_t layer = get_highest_layer(layer_state);
    if (is_layer_locked(layer)) {
        layer_lock_off(layer);
        return true;
    }
    return false;
}

// Wiggle the mouse pointer in a small zig-zag so macOS enlarges it
static void shake_mouse(void) {
    const int distance = 4;
    register_code16(MS_ACL1);
    for (int i = 0; i < distance; ++i) tap_code(MS_LEFT);
    for (int u = 0; u < 6; ++u) {
        for (int i = 0; i < distance; ++i) { tap_code(MS_RGHT); tap_code(MS_UP); }
        for (int i = 0; i < distance; ++i) { tap_code(MS_RGHT); tap_code(MS_DOWN); }
        for (int i = 0; i < distance; ++i) { tap_code(MS_LEFT); tap_code(MS_DOWN); }
        for (int i = 0; i < distance; ++i) { tap_code(MS_LEFT); tap_code(MS_UP); }
    }
    for (int i = 0; i < distance; ++i) tap_code(MS_RGHT);
    unregister_code16(MS_ACL1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Shift + GUI + Backspace deletes to end of line (Ctrl-K)
    if (keycode == KC_BACKSPACE && check_mods_sft_and_gui()) {
        if (record->event.pressed) {
            tap_code16_no_mod(LCTL(KC_K));
            return false;
        }
        // Mods are restored after tap_code16_no_mod(), so clear one-shot mods on release
        if (ONESHOT_MODS_ACTIVE) {
            clear_oneshot_mods();
            send_keyboard_report();
        }
    }

    // Feature order matters: each one can consume the key and stop the rest.
    // QMK also runs Layer Lock after this function, but by then the features below may have
    // consumed layer keys (MO/LT). Run it here first so those keys still unlock a locked layer.
    if (!process_layer_lock(keycode, record)) {
        return false;
    }
    if (!process_magic_shift(keycode, record)) {
        return false;
    }
    if (!process_cmd_tab_switcher(keycode, record)) {
        return false;
    }
    if (!process_oneshot_mods(keycode, record)) {
        return false;
    }
    if (!process_symbol_rolls(keycode, record, SYMBL)) {
        return false;
    }
    if (IS_LAYER_ON(BASE) && !process_mash_arrows(keycode, record)) {
        return false;
    }
    if (!process_mo_ext(keycode, record)) {
        return false;
    }
    if (!process_long_press_keys(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case TGL_LYT: // Switch the default layer between Serenity and QWERTY
            if (record->event.pressed) {
                layer_off(HRDWR);
                if (IS_LAYER_ON(BASE)) {
                    layer_off(BASE);
                    layer_on(QWRTY);
                    default_layer_set(QWRTY);
                } else {
                    layer_off(QWRTY);
                    layer_on(BASE);
                    default_layer_set(BASE);
                }
            }
            return false;
        case LSFT(LGUI(KC_BSPC)):
            if (record->event.pressed) {
                tap_code16(LCTL(KC_K)); // Delete to end of line
            }
            break;
        // Plain Backspace/Delete, bypassing custom shift keys
        case OS_BSPC:
            if (record->event.pressed) {
                register_code(KC_BACKSPACE);
            } else {
                unregister_code(KC_BACKSPACE);
            }
            break;
        case OS_DEL:
            if (record->event.pressed) {
                register_code(KC_DELETE);
            } else {
                unregister_code(KC_DELETE);
            }
            break;
        case ENC_BTN: // Encoder push button
            if (record->event.pressed) {
                if (MODS_SFT) {
                    tap_code16_no_mod(OS_DRKMD_TGL);
                } else if (MODS_CTRL) {
                    tap_code16_no_mod(ZOOM_RESET);
                } else if (MODS_ALT) {
                    tap_code16_no_mod(ZOOM_RESET_APP);
                } else if (MODS_GUI) {
                    tap_code16(KC_H); // Cmd-H: hide app
                } else {
                    tap_code(KC_MUTE);
                }
                return false;
            }
            break;
        case SHAKE_MOUSE:
            if (record->event.pressed) {
                shake_mouse();
            }
            break;
        case KC_ESC:
            if (record->event.pressed && escape_cancels_something()) {
                return false; // Don't send Escape
            }
            break;
        case LT(MOUSE, KC_ESC):
            if (record->tap.count > 0 && record->event.pressed && escape_cancels_something()) {
                return false; // Don't send Escape
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
#ifdef QWERTY_BASE
    layer_off(BASE);
    layer_on(QWRTY);
    default_layer_set(QWRTY);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    cmd_tab_switcher_layer_state(state);

    // Cancel one-shot mods when moving to most layers
    switch (get_highest_layer(state)) {
        case BASE:
        case QWRTY:
        case ACTN:
        case HRDWR:
            break; // Keep them (ACTN and HRDWR need them for function keys)
        default:
            cancel_oneshot_mods_if_active();
            break;
    }

    state = update_tri_layer_state(state, NUMNAV, SYMBL, OS);
    state = update_tri_layer_state(state, HRDWR, ACTN, FUNC);

#ifdef KEY_LOCK_ENABLE
    cancel_key_lock();
#endif

    return state;
}

void matrix_scan_user(void) {
    cmd_tab_switcher_matrix_scan_user();
    oneshot_mods_task(); // Enforce one-shot timeout
}
