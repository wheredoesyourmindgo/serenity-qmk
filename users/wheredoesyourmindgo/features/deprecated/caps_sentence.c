#include "caps_sentence.h"

static bool caps_sentence_active = false;

// Many keyboards enable the Command feature, which by default is also activated
// by Left Shift + Right Shift. It can be configured to use a different key
// combination by defining IS_COMMAND(). We make a non-fatal warning if Command
// is enabled but IS_COMMAND() is *not* defined.
#if defined(COMMAND_ENABLE) && !defined(IS_COMMAND)
#pragma message \
    "Caps Sentence and Command should not be enabled at the same time, since both use the Left Shift + Right Shift key combination. Please disable Command, or ensure that `IS_COMMAND` is not set to (get_mods() == MOD_MASK_SHIFT)."
#endif  // defined(COMMAND_ENABLE) && !defined(IS_COMMAND)

#if CAPS_SENTENCE_IDLE_TIMEOUT > 0
#if CAPS_SENTENCE_IDLE_TIMEOUT < 100 || CAPS_SENTENCE_IDLE_TIMEOUT > 30000
// Constrain timeout to a sensible range. With the 16-bit timer, the longest
// representable timeout is 32768 ms, rounded here to 30000 ms = half a minute.
#error "caps_sentence: CAPS_SENTENCE_IDLE_TIMEOUT must be between 100 and 30000 ms"
#endif

static uint16_t idle_timer = 0;

void caps_sentence_task(void) {
  if (caps_sentence_active && timer_expired(timer_read(), idle_timer)) {
    caps_sentence_off();
  }
}
#endif  // CAPS_SENTENCE_IDLE_TIMEOUT > 0

bool process_caps_sentence(uint16_t keycode, keyrecord_t* record, uint16_t CAPS_SENTENCE) {

#ifndef NO_ACTION_ONESHOT
  const uint8_t mods = get_mods() | get_oneshot_mods();
#else
  const uint8_t mods = get_mods();
#endif  // NO_ACTION_ONESHOT

  if (!caps_sentence_active) {
    if (keycode == CAPS_SENTENCE) {
      caps_sentence_on();
      return false;
    }
    return true;
  } else {
#if CAPS_SENTENCE_IDLE_TIMEOUT > 0
    idle_timer = record->event.time + CAPS_SENTENCE_IDLE_TIMEOUT;
#endif  // CAPS_SENTENCE_IDLE_TIMEOUT > 0
  }

  if (!record->event.pressed) {
    return true;
  }

  if (!(mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT)))) {
    switch (keycode) {
      // Ignore MO, TO, TG, TT, and OSL layer switch keys.
      case QK_MOMENTARY ... QK_MOMENTARY_MAX:
      case QK_TO ... QK_TO_MAX:
      case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
      case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
      case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
      // Ignore AltGr.
      case KC_RALT:
      case OSM(MOD_RALT):
        return true;

#ifndef NO_ACTION_TAPPING
      case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        if (record->tap.count == 0) {  // Mod-tap key is held.
          // Corresponding to how mods are handled above:
          // * For shift mods, pass KC_LSFT or KC_RSFT to caps_sentence_press_user()
          //   to determine whether to continue Caps Sentence.
          // * For Shift + AltGr (MOD_RSFT | MOD_RALT), pass RSFT(KC_RALT).
          // * AltGr (MOD_RALT) is ignored.
          // * Otherwise stop Caps Sentence.
          const uint8_t mods = (keycode >> 8) & 0x1f;
          switch (mods) {
            case MOD_LSFT:
              keycode = KC_LSFT;
              break;
            case MOD_RSFT:
              keycode = KC_RSFT;
              break;
            case MOD_RSFT | MOD_RALT:
              keycode = RSFT(KC_RALT);
              break;
            default:
              if (mods != MOD_RALT) {
                caps_sentence_off();
              }
              return true;
          }
        } else {
          keycode &= 0xff;
        }
        break;

#ifndef NO_ACTION_LAYER
      case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#endif  // NO_ACTION_LAYER
        if (record->tap.count == 0) {
          return true;
        }
        keycode &= 0xff;
        break;
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
      case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
        if (keycode > 0x56F0 || record->tap.count == 0) {
          return true;
        }
        keycode &= 0xff;
        break;
#endif  // SWAP_HANDS_ENABLE
    }

    clear_weak_mods();
    if (caps_sentence_press_user(keycode)) {
      send_keyboard_report();
      return true;
    }
  }

  caps_sentence_off();
  return true;
}

void caps_sentence_on(void) {
  if (caps_sentence_active) {
    return;
  }

  clear_mods();
#ifndef NO_ACTION_ONESHOT
  clear_oneshot_mods();
#endif  // NO_ACTION_ONESHOT
#if CAPS_SENTENCE_IDLE_TIMEOUT > 0
  idle_timer = timer_read() + CAPS_SENTENCE_IDLE_TIMEOUT;
#endif  // CAPS_SENTENCE_IDLE_TIMEOUT > 0

  caps_sentence_active = true;
  caps_sentence_set_user(true);
}

void caps_sentence_off(void) {
  if (!caps_sentence_active) {
    return;
  }

  unregister_weak_mods(MOD_BIT(KC_LSFT));  // Make sure weak shift is off.
  caps_sentence_active = false;
  caps_sentence_set_user(false);
}

void caps_sentence_toggle(void) {
  if (caps_sentence_active) {
    caps_sentence_off();
  } else {
    caps_sentence_on();
  }
}

bool is_caps_sentence_on(void) { return caps_sentence_active; }

__attribute__((weak)) void caps_sentence_set_user(bool active) {}

__attribute__((weak)) bool caps_sentence_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Sentence, with shift applied.
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Sentence, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case KC_MINS:
      return true;

    default:
      return false;  // Deactivate Caps Sentence.
  }
}
