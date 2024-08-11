/*
Copyright 2024 @sizezero

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include "keymap_introspection.h"
#include "print.h"

// when the keyboard is plugged in, the caps lock toggle may be out of sync with the computer
// re-sync it
void sync_caps_lock(uint8_t layer_num, uint8_t row, uint8_t column) {
    dprint("sync_caps_lock()\n");
    if (KC_LCAP == keycode_at_keymap_location(layer_num, row, column)) {
        dprintf("KC_LCAP in layout at layer:%d row:%d column:%d\n", layer_num, row, column);
        led_t led_state = host_keyboard_led_state();
        if (led_state.caps_lock) {
            dprint("caps lock on\n");
            if (matrix_is_on(row, column)) {
                // caps lock is on and toggle key is on so do nothing
            } else {
                // caps lock is on and toggle key is not depressed
                dprint("toggling caps lock\n");
                // programmatically send a keycode that toggle caps lock on
                tap_code(KC_CAPS_LOCK);
            }
        } else { // caps lock state is off
            dprint("caps lock off\n");
            if (matrix_is_on(row, column)) {
                // caps lock is off and toggle key is on
                dprint("toggling caps lock\n");
                // programmatically send a keycode that toggle caps lock on
                tap_code(KC_CAPS_LOCK);
            } else {
                // caps lock is off and toggle key is off so do nothing
            }
        }
    } else {
        dprintf("KC_LCAP NOT in layout at layer:%d row:%d column:%d\n", layer_num, row, column);
    }
}

// when the keyboard is plugged in, the layer toggle switch may be out of sync with the default layer
// re-sync it
void sync_toggle_layer_2(uint8_t layer_num, uint8_t row, uint8_t column) {
    dprint("sync_toggle layer()\n");
    if (IS_QK_TOGGLE_LAYER(keycode_at_keymap_location(layer_num, row, column))) {
        dprintf("TG() in layout at layer:%d row:%d column:%d\n", layer_num, row, column);
        if (matrix_is_on(row, column)) {
           // switch is depressed, toggle our layer to 2
           dprint("toggling TG(2)\n");
           // programmatically send a keycode that toggles layer 2
           layer_invert(2);
        }
    } else {
        dprintf("TG() is NOT in layout at layer:%d row:%d column:%d\n", layer_num, row, column);
    }
}

