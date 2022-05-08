
// !!! DO NOT ADD #pragma once !!! //

// This animation is attempting to light each led in led index
// order. Each call of the animation lights a single led and turns all
// the others off by resetting them to black.

// The actual effect is to light them in led index order, however,
// instead of a single led being lit, THREE leds are lit at a
// time. For the life of me, I can't figure out how the following code
// could light three leds at once instead of just one.

// a video of this animation is available here:
// https://www.youtube.com/watch?v=ZrSnJVIb2kc

// Note: I have tested this hardware with a number of the stock
// animations and they appear to work fine, so the problem is likely
// not wiring/soldering/soldering or hardware related.

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  // magic time taken from BREATHING animation
  uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 100);
  // determine the primary led index
  uint8_t pi = (time % (led_max - led_min)) + led_min;
  
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();

    // only light the primary led
    if (i == pi) {
      HSV hsv = {0xc0, 0xc0, 100};
      RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    } else {
      rgb_matrix_set_color(i, 0, 0, 0);
    }

   }
  
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
