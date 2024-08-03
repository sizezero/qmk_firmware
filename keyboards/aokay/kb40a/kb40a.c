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
#include "deferred_exec.h"

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

uint32_t my_callback(uint32_t trigger_time, void *cb_arg) {
  sync_caps_lock(0, 4, 10);
  sync_caps_lock(0, 4, 11);
  return 0; // don't repeat this callback
}

// leftmost toggle key is at matrix (4,10)
void keyboard_post_init_kb(void) {
  keyboard_post_init_user();
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  defer_exec(2000, my_callback, NULL);
}
