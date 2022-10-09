// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "lyr_on_dual.h"
#include "wheredoesyourmindgo.h"

bool process_layer_on_dual_hold(uint16_t keycode, keyrecord_t* record) {

    switch (keycode) {
        case LT(NUMNAV, KC_ESC):
            if (record->event.pressed) {
                // Only during layer hold
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(AUX)) {
                        layer_off(AUX);
                        layer_on(OS);
                        return false;
                    }
                }
            } else {
                if (IS_LAYER_ON(OS)) {
                    layer_off(OS);
                    layer_on(AUX);
                    return false;
                }
            }
            break;
        case LT(AUX, KC_TAB):
            if (record->event.pressed) {
                // Only during layer hold
                if (!(record->tap.count > 0)) {
                    if (IS_LAYER_ON(NUMNAV)) {
                        layer_off(NUMNAV);
                        layer_on(OS);
                        return false;
                    }
                }
            } else {
                if (IS_LAYER_ON(OS)) {
                    layer_off(OS);
                    layer_on(NUMNAV);
                    return false;
                }
            }
            break;
    }

  return true;
}
