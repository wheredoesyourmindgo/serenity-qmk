#include "custom_gui_keys.h"

bool process_custom_gui_keys(uint16_t keycode, keyrecord_t *record) {
  static uint16_t registered_keycode = KC_NO;

  // If a custom shift key is registered, then this event is either releasing
  // it or manipulating another key at the same time. Either way, we release
  // the currently registered key.
  if (registered_keycode != KC_NO) {
    unregister_code16(registered_keycode);
    registered_keycode = KC_NO;
  }

  if (record->event.pressed) {  // Press event.
    const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    if ((mods | get_weak_mods() | get_oneshot_mods()) & MOD_MASK_GUI) {
#else
    if ((mods | get_weak_mods()) & MOD_MASK_GUI) {  // Shift is held.
#endif  // NO_ACTION_ONESHOT
      // Search for a custom key with keycode equal to `keycode`.
      for (int i = 0; i < NUM_CUSTOM_GUI_KEYS; ++i) {
        if (keycode == custom_gui_keys[i].keycode) {
          // Continue default handling if this is a tap-hold key being held.
          if (((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX) ||
               (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) &&
              record->tap.count == 0) {
            return true;
          }
#ifndef NO_ACTION_ONESHOT
          del_oneshot_mods(MOD_MASK_GUI);
#endif  // NO_ACTION_ONESHOT
          del_mods(MOD_MASK_GUI);
          del_weak_mods(MOD_MASK_GUI);
          send_keyboard_report();
          registered_keycode = custom_gui_keys[i].modded_keycode;
          register_code16(registered_keycode);
          set_mods(mods);  // Restore the mods.
          return false;
        }
      }
    }
  }

  return true;  // Continue with default handling.
}
