#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint16_t keycode;
  uint16_t modded_keycode;
} custom_gui_key_t;

extern const custom_gui_key_t custom_gui_keys[];
extern uint8_t NUM_CUSTOM_GUI_KEYS;

bool process_custom_gui_keys(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif
