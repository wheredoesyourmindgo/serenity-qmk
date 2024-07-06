#pragma once

#define TAPPING_TERM 200
#define OSM_TAPPING_TERM 300
#define MO_EXT_TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY
// #define TAPPING_TOGGLE 2

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 64

// #define RGBLIGHT_SLEEP true
// #define DEBUG_ACTION

// #define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// Enable per key rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM_PER_KEY
#define RETRO_TAPPING_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Capsword, using RSFT_T(KC_ENT) so both shifts is not ideal, use double tap left shift instead
// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// #define LEADER_PER_KEY_TIMING
// #define LEADER_TIMEOUT 250

// Keyboard specific
#if defined SIGNUM_KEYBOARD
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 5
#elif defined BOARDWALK_KEYBOARD
// #define MOUSEKEY_INTERVAL       12
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed, defaults to 5 for Boardwalk */
//  #undef DEBOUNCE
//  #define DEBOUNCE 10
#elif defined PLANCK_KEYBOARD
    #if ENCODER_ENABLE
    #define ENCODER_RESOLUTION 2
    #endif
#elif defined RISTRETTO_KEYBOARD
#define ENCODER_DIRECTION_FLIP
#endif
