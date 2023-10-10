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
    LAYER_GAMING_TOGGLE,
    LAYER_DOTA,
    LAYER_ALIEN,
    LAYER_ALIEN_SHIFT
};

// begin: copy and pasted oled code

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void render_keylock_status(led_t led_state) {
  if (led_state.caps_lock) {
    oled_write_ln_P(PSTR("CAPS LOCK"), true);
  } else {
    oled_write_ln_P(PSTR(""), false);
  }
}

// TODO: the original layers were defined as powers of two, maybe this
// won't work
void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case LAYER_BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case LAYER_GAMING:
            oled_write_ln_P(PSTR("Gaming"), false);
            break;
        case LAYER_DOTA:
            oled_write_ln_P(PSTR("DOTA"), false);
            break;
        case LAYER_ALIEN:
            oled_write_ln_P(PSTR("Alien"), false);
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

/*
 * custom logo that says "Kleemann" and has a clover
 *
 * The project for this was found here
 * https://github.com/joric/qle
 * which leads to this site
 * https://joric.github.io/qle/
 *
 * ...which lets you download a template image, modify it, and then
 * reload to generate code. I decided not to futz with the original
 * fonts so I used the raw image data which takes a little more space.
 */
static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,128,128,184,252,252,254,252,252,184,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0, 15,159,159,159,159,143,255,207,159,159,159,159, 15,  0,224,224,224,224,  0,  0,  0,128,192,224,224, 96, 32,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,255,255,255,255,124,254,255,231,195,129,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,240,248,252,254,110,102,102,110,126,124,124,112,  0,  0,240,248,252,254,110,102,102,110,126,124,124,112,  0,  0,  0,254,254,254,254, 12,  6,  6,254,254,252,248, 12,  6,  6,254,254,252,248,  0,  0,128,204,230,230,102,102,102,254,254,252,248,  0,  0,  0,254,254,254,254, 12,  4,  6,254,254,252,248,  0,  0,  0,254,254,254,254, 12,  4,  6,254,254,252,248,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15,  0,  0,  1,  3,  7, 15, 15, 14, 12,  8,  0, 15, 15, 15, 15,  0,  0,  1,  3,  7, 15, 14, 12, 12, 12, 12, 12,  6,  0,  0,  0,  1,  3,  7, 15, 14, 12, 12, 12, 12, 12,  6,  0,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  3,  7, 15, 15, 12, 12,  6, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void oled_render_alien_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,224,224,224,224,224,192,  0,  0,  0,128,224,224,224,224,224,224,224,224,224,224,  0,  0,128,224,224,224,224,224,224,224,224,224,224,  0,  0,  0,  0,  0,128,128,192,192,224,224,224,224,224,224,224,224,192,  0,  0,  0,128,192,192,224,224,224,224,224,224,192,  0,  0,  0,  0,  0,  0,128,192,192,224, 96, 96, 96,224,224,192,128,  0,  0,  0,  0,  0,192,224,224,224,224,192,  0,  0,  0,  0,  0,  0,192,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 63,127,127,255,249,240,240,225,225,193,  0,  0,128,252,255,255,255,119,112,112,112,112,112,  0,  0,128,252,255,255,255,119,112,112,112,112,112,  0,  0,  0,224,248,254,255, 15,  7,  3,  1,  1,225,225,225,225,225,225,193,  0,  0, 12, 63,127,127,255,249,240,240,225,225,193,  0,  0,  0,240,252,254,255,  7,  3,  0,  0,  0,  0,  0,  0,129,255,255,255,126,  0,128,252,255,255,255,  7, 63,255,254,248,224,  0,128,252,255,255,255,  7,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,120,120,112,112,112,112,121, 63, 31, 31,  7,  0, 16,127,127,127,127,112,112,112,112,112,112, 48,  0, 16,127,127,127,127,112,112,112,112,112,112, 48,  0,  0,  0,  7, 31, 63, 63,124,120,112,112,112,112,120,127, 63, 63, 15,  0,  0, 48,120,120,112,112,112,112,121, 63, 31, 31,  7,  0,  0,  0, 15, 31, 63, 63,112, 96, 96, 96, 96,112, 56, 60, 31, 15,  7,  3,  0, 48,127,127, 63, 31,  0,  0,  0,  0,  7, 63,127,127,127,127, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    layer_state_t layer = get_highest_layer(layer_state);
    if (layer==LAYER_ALIEN || layer==LAYER_ALIEN_SHIFT) {
      oled_render_alien_logo();
    } else {
      oled_clear(); // needed to wipe the alien logo
      oled_render_layer_state();
      render_keylock_status(host_keyboard_led_state());
      oled_render_keylog();
    }
  } else {
    oled_render_logo();
  }
  return false;
}


// special keycodes for Alien Isolation
//enum my_keycodes {
//  PEEK_W = SAFE_RANGE,
//  PEEK_A,
//  PEEK_S,
//  PEEK_D
//};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // show the keycoad on the OLED
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  // new macros
  switch(keycode) {
  case QK_MACRO_0:
    if (record->event.pressed) {
      register_code(KC_V);
      register_code(KC_W);
    } else {
      unregister_code(KC_W);
      unregister_code(KC_V);
    }
    break;
  case QK_MACRO_1:
    if (record->event.pressed) {
      register_code(KC_V);
      register_code(KC_A);
    } else {
      unregister_code(KC_A);
      unregister_code(KC_V);
    }
    break;
  case QK_MACRO_2:
    if (record->event.pressed) {
      register_code(KC_V);
      register_code(KC_S);
    } else {
      unregister_code(KC_S);
      unregister_code(KC_V);
    }
    break;
  case QK_MACRO_3:
    if (record->event.pressed) {
      register_code(KC_V);
      register_code(KC_D);
    } else {
      unregister_code(KC_D);
      unregister_code(KC_V);
    }
    break;
  case QK_MACRO_4:
    // simulate numlock 1 for wc3
    if (record->event.pressed) {
      register_code(KC_NUM);
      register_code(KC_P1);
    } else {
      unregister_code(KC_P1);
      unregister_code(KC_NUM);
    }
    break;
  case QK_MACRO_5:
    // simulate numlock 2 for wc3
    if (record->event.pressed) {
      register_code(KC_NUM);
      register_code(KC_P2);
    } else {
      unregister_code(KC_P2);
      unregister_code(KC_NUM);
    }
    break;
  default:
    break;
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
  // break out if we are not in one of our custom modes
  switch(rgb_matrix_get_mode()) {
  case RGB_MATRIX_CUSTOM_animation_base:
  case RGB_MATRIX_CUSTOM_animation_navigation:
  case RGB_MATRIX_CUSTOM_animation_braces:
  case RGB_MATRIX_CUSTOM_animation_window_manager:
  case RGB_MATRIX_CUSTOM_animation_numpad:
  case RGB_MATRIX_CUSTOM_animation_symbol:
  case RGB_MATRIX_CUSTOM_animation_function:
    break;
  default:
    return state;
  }
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

