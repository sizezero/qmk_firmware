
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
  //uint8_t pi = (time % (led_max - led_min)) + led_min;
  uint8_t pi0 = (time % (DRIVER_LED_TOTAL - 0)) + 0;
  uint8_t pi1 = ((pi0-1) % (DRIVER_LED_TOTAL - 0)) + 0;
  uint8_t pi2 = ((pi1-1) % (DRIVER_LED_TOTAL - 0)) + 0;
  uint8_t pi3 = ((pi2-1) % (DRIVER_LED_TOTAL - 0)) + 0;
  uint8_t pi4 = ((pi3-1) % (DRIVER_LED_TOTAL - 0)) + 0;

  //uprintf("led_min:%d led_max:%d time:%d pi:%d total:%d\n", led_min,
  // led_max, time, pi, DRIVER_LED_TOTAL); The above debug statement
  // shows that the corne has a DRIVER_LED_TOTAL of 54. This function
  // is getting called three times with led_min/max of (0,11) (11,22)
  // (22,27). Only have half the keyboard is plugged in so I would
  // expect it to go all the way up to 54 if the other half was
  // plugged in. It seems led_min, led_max is just what leds are
  // expected to change for this call and are not representative of
  // the total number of leds. I should instead use
  // (0,DRIVER_LED_TOTAL) for normalization.

  HSV hsv = {0xc0, 0xc0, 100};
  
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();

    // only light the primary led
    if (i == pi0) {
      hsv.v = 150;
    } else if (i == pi1) {
      hsv.v = 100;
    } else if (i == pi2) {
      hsv.v = 75;
    } else if (i == pi3) {
      hsv.v = 50;
    } else if (i == pi4) {
      hsv.v = 25;
    } else {
      hsv.v = 0;
    }
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
   }
  
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
