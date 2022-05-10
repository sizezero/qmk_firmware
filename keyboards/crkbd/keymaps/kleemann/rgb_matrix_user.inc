
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

// to run the console you need to:
// in rules.mk:
//   CONSOLE_ENABLE = yes
//   OLED_ENABLE = no # due to mem
//   LTO_ENABLE = no  # due to mem
// default.c:
//   debug_enable = true
//   debug_matrix = true
// from console:
//   $ qmk console

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

// I think on the corne, init "if (params->init)" is getting called
// about three times. It is probably called once with each of the led
// ranges.

// Informally logged uint32 g_rgb_timer. In 60 seconds it reached up
// to 59K. a few seconds later it underflowed back to 0. This means 1
// second is about 980 ticks. I have no idea if this can be counted on
// or if it is just based on each microcontroller.

// TODO: make a function that accepts a chain of keys/colors

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef struct PACKED {
  HSV hsv;
  uint8_t led_id;
} path_node_t;

static void draw_path_nodes(path_node_t* ns, uint8_t count, uint8_t led_min, uint8_t led_max) {

  // magic time taken from BREATHING animation. It seems to range
  // between 0 and 255.
  //uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 100);

  //uprintf("led_min:%d led_max:%d time:%d g_rgb_timer:%u total:%d\n", led_min, led_max, time, g_rgb_timer, DRIVER_LED_TOTAL);

  const uint32_t step = 200; // 980 about a second of g_rgb_timer
  const uint32_t fade = 6;   // the number of nodes before intesity fades to nothing
  const uint32_t space = step*fade*2; // push out the x axis so we don't have to deal with wrapping
  const uint8_t max_intensity = 150;
  const uint64_t rt = (g_rgb_timer % (count*step)) + space;
  const uint64_t lower = rt - step*fade;

  HSV hsv;

  for (uint8_t i = led_min; i < led_max; i++) {

    hsv.h = 0;
    hsv.s = 0;
    hsv.v = 0;

    // TODO: this is super inefficient
    for (uint8_t in = 0 ; in < count ; in++) {
      if (ns[in].led_id == i) {
        uint64_t inrt = in*step + space;
        if (lower < inrt && inrt <= rt) {
          hsv.h = ns[in].hsv.h;
          hsv.s = ns[in].hsv.s;
          hsv.v = ((inrt - lower) * max_intensity) / (step*fade);
          //uprintf("led:%d, node:%d value:%d", i, in, hsv.v);
          break;
        }
      }
    }

    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

path_node_t pn_numpad[] = {
  // 1-9
  { {170, 255, 0}, 20},
  { {170, 255, 0}, 15},
  { {170, 255, 0}, 12},
  { {170, 255, 0}, 19},
  { {170, 255, 0}, 16},
  { {170, 255, 0}, 11},
  { {170, 255, 0}, 18},
  { {170, 255, 0}, 17},
  { {170, 255, 0}, 10},

  // 0 in two places
  { {170, 255, 0}, 9},
  { {170, 255, 0}, 25},

  // the final two symbols
  { {35, 255, 0}, 8},
  { {35, 255, 0}, 7},

  // add some null nodes just for spacing
  { {0, 0, 0}, 255},
  { {0, 0, 0}, 255},
  { {0, 0, 0}, 255},
  { {0, 0, 0}, 255},
};

static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  draw_path_nodes(pn_numpad, sizeof(pn_numpad)/sizeof(pn_numpad[0]), led_min, led_max);

  return rgb_matrix_check_finished_leds(led_max);
}

static uint8_t init_index = 0;

static bool my_cool_effect2(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  // magic time taken from BREATHING animation
  uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 100);
  // determine the primary led index
  //uint8_t pi = (time % (led_max - led_min)) + led_min;
  uint8_t pi0 = time % DRIVER_LED_TOTAL;
  uint8_t pi1 = (pi0-1 +DRIVER_LED_TOTAL) % DRIVER_LED_TOTAL;
  uint8_t pi2 = (pi1-1 +DRIVER_LED_TOTAL) % DRIVER_LED_TOTAL;
  uint8_t pi3 = (pi2-1 +DRIVER_LED_TOTAL) % DRIVER_LED_TOTAL;
  uint8_t pi4 = (pi3-1 +DRIVER_LED_TOTAL) % DRIVER_LED_TOTAL;

  if (params->init) {
    // just to see how many times init is called. Check with both
    // halves of the keyboard enabled.
    //uprintf("led_min:%d led_max:%d time:%d pi:%d total:%d\n", led_min, led_max, time, pi0, DRIVER_LED_TOTAL);
    // the above call is not getting sent problably because it is happening so close to startup

    // we can inspect this during a later cycle
    ++init_index;
  }
  uprintf("led_min:%d led_max:%d time:%d pi:%d total:%d init:%d\n", led_min, led_max, time, pi0, DRIVER_LED_TOTAL, init_index);

  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();

    HSV hsv = {0xc0, 0xc0, 100};

    // only light the primary led
    if (i == init_index) {
      // we'll have to count how far this goes into the indexes to see
      // how many times init was called
      hsv.h = 0;
      hsv.s = 255;
      hsv.v = 150;
    } else if (i == pi0) {
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
