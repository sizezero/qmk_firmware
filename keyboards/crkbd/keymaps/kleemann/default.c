/*
Copyright 2019 @foostan
Copyright 2022 Robert Kleemann

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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    LAYER_BASE,
    LAYER_NAV,
    LAYER_NUMPAD,
    LAYER_SHIFT_NUMPAD,
    LAYER_RESET,
    LAYER_WINDOW_MANAGER,
    LAYER_BRACES,
    LAYER_FUNCTION_KEYS,
    LAYER_GAMING,
    LAYER_GAMING_TOGGLE
};

// begin: copy and pasted oled code

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

// TODO: the original layers were defined as powers of two, maybe this
// won't work
void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case LAYER_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case LAYER_GAMING:
            oled_write_ln_P(PSTR("Gaming"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE

// end: copy and pasted oled code

// kleemann

#ifdef RGB_MATRIX_ENABLE
//void keyboard_post_init_user(void) {

  // one time disable of rgb matrix for default
  //rgb_matrix_disable();

  // No matter what I do, RGB underglow #1 lights up green 80% of the
  // time on startup. It must be a hardware issue, maybe a bad
  // solder. The temporary workaround is to turn lighting on and off
  // via keystrokes.
  //rgb_matrix_enable_noeeprom();
  //rgb_matrix_set_color_all(0, 0, 0);
  //rgb_matrix_sethsv_noeeprom(0, 0, 0);
  //rgb_matrix_disable_noeeprom();

  // needed for console debugging
  //debug_enable = true;
  //debug_matrix = true;

  // these were used for testing; leaving them here as an FYI
  //rgb_matrix_set_color_all(0, 255, 0); // works
  //rgb_matrix_sethsv(191, 43, 81);
  //rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
  //rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_base);
  //rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_navigation);
//}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case LAYER_BASE:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_base);
      break;
    case LAYER_NAV:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_navigation);
      break;
    case LAYER_BRACES:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_braces);
      break;
    case LAYER_WINDOW_MANAGER:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_window_manager);
      break;
    case LAYER_NUMPAD:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_numpad);
      break;
    case LAYER_SHIFT_NUMPAD:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_symbol);
      break;
    case LAYER_FUNCTION_KEYS:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_animation_function);
      break;
    default:
      rgb_matrix_sethsv_noeeprom(0, 0, 0);
      break;
    }
    return state;
}

#endif

