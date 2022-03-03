// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "lyr_on_dual.h"
#include "wheredoesyourmindgo.h"

bool process_layer_on_dual_hold(uint16_t keycode, keyrecord_t* record) {

    switch (keycode) {
        case LT(LOWER, KC_ESC):
            if (record->event.pressed) {
                // Only during layer hold
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(HIGHER)) {
                        layer_off(HIGHER);
                        layer_on(OS);
                        return false;
                    }
                }
            } else {
                if (IS_LAYER_ON(OS)) {
                    layer_off(OS);
                    layer_on(HIGHER);
                    return false;
                }
            }
            break;
        case LT(HIGHER, KC_SPC):
            if (record->event.pressed) {
                // Only during layer hold
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(LOWER)) {
                        layer_off(LOWER);
                        layer_on(OS);
                        return false;
                    }
                }
            } else {
                if (IS_LAYER_ON(OS)) {
                    layer_off(OS);
                    layer_on(LOWER);
                    return false;
                }
            }
            break;
    }

  return true;
}
