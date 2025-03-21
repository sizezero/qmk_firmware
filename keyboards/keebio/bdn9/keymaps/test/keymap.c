#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, RM_NEXT
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            rgblight_increase_sat();
        } else {
            rgblight_decrease_sat();
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
    }
    return true;
}
