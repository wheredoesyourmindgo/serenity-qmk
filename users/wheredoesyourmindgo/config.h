#pragma once

#define TAPPING_TERM 200
#define TAPPING_TD_TERM 250
#define TAPPING_TERM_PER_KEY

// Auto Shift and Retro Shift (Auto Shift for Tap Hold).
// #define AUTO_SHIFT_TIMEOUT TAPPING_TERM
// #define AUTO_SHIFT_NO_SETUP
// #define RETRO_SHIFT 500

// Recommended for heavy chording.
// #define QMK_KEYS_PER_SCAN 4

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

// #define DEBUG_ACTION

// Combos
// #define COMBO_COUNT 1
// #define COMBO_ALLOW_ACTION_KEYS

// Prevent normal rollover on alphas from accidentally triggering mods (only with alpha keys).
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// Enable per key rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD_PER_KEY

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
