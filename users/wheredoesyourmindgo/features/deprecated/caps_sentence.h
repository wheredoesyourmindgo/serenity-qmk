#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Handler function for Caps Sentence.
 *
 * Call this function from `process_record_user()` to implement Caps Sentence.
 */
bool process_caps_sentence(uint16_t keycode, keyrecord_t* record, uint16_t CAPS_SENTENCE);

// If CAPS_SENTENCE_IDLE_TIMEOUT is set, call `caps_sentence_task()` from
// `matrix_scan_user()` as described above.
//
// If CAPS_SENTENCE_IDLE_TIMEOUT isn't set, calling this function has no effect (but
// will still compile).
#if CAPS_SENTENCE_IDLE_TIMEOUT > 0
void caps_sentence_task(void);
#else
static inline void caps_sentence_task(void) {}
#endif

/**
 * Turns on Caps Sentence.
 *
 * For instance activate Caps Sentence with a combo by defining a `COMBO_ACTION`
 * that calls `caps_sentence_on()`:
 *
 * void process_combo_event(uint16_t combo_index, bool pressed) {
 *   switch(combo_index) {
 *     case CAPS_COMBO:
 *       if (pressed) {
 *         caps_sentence_on();
 *       }
 *       break;
 *
 *     // Other combos...
 *   }
 * }
 */
void caps_sentence_on(void);

/** Turns off Caps Sentence. */
void caps_sentence_off(void);

/** Toggles Caps Sentence. */
void caps_sentence_toggle(void);

/** Returns true if Caps Sentence is currently on. */
bool is_caps_sentence_on(void);

/**
 * Optional callback that gets called when Caps Sentence turns on or off.
 *
 * This callback is useful to represent the current Caps Sentence state, e.g. by
 * setting an LED or playing a sound. In your keymap, define
 *
 *     void caps_sentence_set_user(bool active) {
 *       if (active) {
 *         // Do something when Caps Sentence activates.
 *       } else {
 *         // Do something when Caps Sentence deactivates.
 *       }
 *     }
 */
void caps_sentence_set_user(bool active);

/**
 * Optional callback, called on each key press while Caps Sentence is active.
 *
 * When the key should be shifted (that is, a letter key), the callback should
 * call `add_weak_mods(MOD_BIT(KC_LSFT))` to shift the key. The callback also
 * determines whether the key should continue Caps Sentence. Returning true
 * continues the current "Sentence", while returning false is "Sentence breaking" and
 * deactivates Caps Sentence. The default callback is
 *
 *     bool caps_sentence_press_user(uint16_t keycode) {
 *       switch (keycode) {
 *         // Keycodes that continue Caps Sentence, with shift applied.
 *         case KC_A ... KC_Z:
 *         case KC_MINS:
 *           add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
 *           return true;
 *
 *         // Keycodes that continue Caps Sentence, without shifting.
 *         case KC_1 ... KC_0:
 *         case KC_BSPC:
 *         case KC_DEL:
 *         case KC_UNDS:
 *           return true;
 *
 *         default:
 *           return false;  // Deactivate Caps Sentence.
 *       }
 *     }
 *
 * To customize, copy the above function into your keymap and add/remove
 * keycodes to the above cases.
 *
 * @note Outside of this callback, you can use `caps_sentence_off()` to deactivate
 * Caps Sentence.
 */
bool caps_sentence_press_user(uint16_t keycode);

// Deprecated APIs.

/** @deprecated Use `caps_sentence_on()` and `caps_sentence_off()` instead. */
static inline void caps_sentence_set(bool active) {
  if (active) {
    caps_sentence_on();
  } else {
    caps_sentence_off();
  }
}

/** @deprecated Use `is_caps_sentence_on()` instead. */
static inline bool caps_sentence_get(void) { return is_caps_sentence_on(); }

#ifdef __cplusplus
}
#endif
