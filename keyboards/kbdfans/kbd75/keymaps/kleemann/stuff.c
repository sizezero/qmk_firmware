#include QMK_KEYBOARD_H

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 4: // gaming layer
    case 5: // gaming toggle layeer
        rgblight_disable_noeeprom();
        break;
    default: //  for any other layers, or the default layer
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(0, 0xff, 0x40); // h=0=red, s=0xff=sharp color, v=0x10 dim
        break;
    }
    return state;
}
