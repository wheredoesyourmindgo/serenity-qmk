#pragma once

#include QMK_KEYBOARD_H

#define ONESHOT_MODS_ACTIVE (get_oneshot_mods())
#define ONESHOT_MODS_LSFT (get_oneshot_mods() & MOD_BIT(KC_LSFT))
#define ONESHOT_MODS_LGUI (get_oneshot_mods() & MOD_BIT(KC_LGUI))
#define ONESHOT_MODS_RGUI (get_oneshot_mods() & MOD_BIT(KC_RGUI))
#define ONESHOT_MODS_LALT (get_oneshot_mods() & MOD_BIT(KC_LALT))
#define ONESHOT_MODS_LCTL (get_oneshot_mods() & MOD_BIT(KC_LCTL))
#define ONESHOT_MODS_RSFT (get_oneshot_mods() & MOD_BIT(KC_RSFT))
#define ONESHOT_MODS_RALT (get_oneshot_mods() & MOD_BIT(KC_RALT))
#define ONESHOT_MODS_RCTL (get_oneshot_mods() & MOD_BIT(KC_RCTL))

bool cancel_oneshot_mods_if_active(void);
bool process_oneshot_mods(uint16_t keycode, keyrecord_t *record);

#ifndef OSM_DEFAULT_TIMEOUT_MS
#    define OSM_DEFAULT_TIMEOUT_MS 3000
#endif

// Set the oneshot timeout in milliseconds (overrides the default).
void set_oneshot_timeout(uint16_t ms);

// Call this periodically (e.g., from matrix_scan_user) to enforce timeout.
void oneshot_mods_task(void);
