// Copyright 2021-2022 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "custom_gui_keys.h"

bool process_custom_gui_keys(uint16_t keycode, keyrecord_t *record) {
  static uint16_t registered_keycode = KC_NO;

  // If a custom gui key is registered, then this event is either
  // releasing it or manipulating another key at the same time. Either way,
  // we release the currently registered key.
  if (registered_keycode != KC_NO) {
    unregister_code16(registered_keycode);
    registered_keycode = KC_NO;
  }

  // Search for a custom key with keycode equal to `keycode`.
  for (int i = 0; i < NUM_CUSTOM_GUI_KEYS; ++i) {
    if (keycode == custom_gui_keys[i].keycode) {
      if (record->event.pressed) {
        const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        if ((mods | get_oneshot_mods()) & MOD_MASK_GUI) {
          del_oneshot_mods(MOD_MASK_GUI);
#else
        if (mods & MOD_MASK_GUI) {
#endif  // NO_ACTION_ONESHOT
          // del_mods() won't work. use unregister_mods() instead
          unregister_mods(MOD_MASK_GUI);
          registered_keycode = custom_gui_keys[i].modded_keycode;
        } else {
          registered_keycode = custom_gui_keys[i].keycode;
          return true; // return true so that custom_shift_keys() is processed
        }

        register_code16(registered_keycode);
        set_mods(mods);  // Restore the mods.
      }

      return false;
    }
  }

  return true;
}
