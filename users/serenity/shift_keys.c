// Custom Shift Keys table for the getreuer/custom_shift_keys community module (options in config.h).
//
// The module reads this table from the keymap, so rules.mk passes this file to QMK via
// INTROSPECTION_KEYMAP_C, which compiles it alongside each keymap.c. Don't add it to SRC.
#include "serenity.h"

const custom_shift_key_t custom_shift_keys[] = {
    {KC_BACKSPACE, KC_DELETE}, // Shift Backspace is delete forward
};
