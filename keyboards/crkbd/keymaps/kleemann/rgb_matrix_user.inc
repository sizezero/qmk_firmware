
// !!! DO NOT ADD #pragma once !!! //

// -----------------------------------------------------------------
// This animation is attempting to light each led in led index
// order. Each call of the animation lights a single led and turns all
// the others off by resetting them to black.

// The algorithm is data driven with the purpose of giving the user
// hints as to the purpose of keys on different layers.

// -----------------------------------------------------------------
// Notes on developing animations

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

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(animation_numpad)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// An element that represents a single LED in a chain that will be
// lit. An array of these structures is a parameter to
// draw_path_nodes()
typedef struct PACKED {
  uint8_t hue;
  uint8_t saturation;
  uint8_t led_id;
  uint8_t parallel;
} path_node_t;

// some defines useful for populating path_node_t
#define HV_BLUE   177, 255
#define HV_PURPLE 191, 255
#define HV_GOLD    35, 255

#define PN_PAR 1
#define PN_SER 0

#define PN_BLACK 0, 0, 255, PN_SER

// Meant to be called from an rgb matrix animation funciton.
//
// ns: an array of path_node_t that will be drawn in order
// count: the number of elements in the ns array
// led_min: the starting led index passed in from the animation function
// led_max: the ending led index plus one passed in from the animation function
static void draw_path_nodes(path_node_t* ns, uint8_t count, uint8_t led_min, uint8_t led_max) {

  //uprintf("led_min:%d led_max:%d time:%d g_rgb_timer:%u total:%d\n", led_min, led_max, time, g_rgb_timer, DRIVER_LED_TOTAL);

  // the count of the number of serial nodes
  uint8_t serial_count = 0;
  for (uint8_t i = 0 ; i<count ; i++) {
    if (ns[i].parallel == PN_SER) {
      serial_count++;
    }
  }

  const uint32_t step = 200; // 980 about a second of g_rgb_timer
  const uint32_t fade = 6;   // the number of nodes before intensity fades to nothing
  const uint32_t space = step*fade*2; // push out the x axis so we don't have to deal with wrapping
  const uint8_t max_intensity = 150;
  const uint64_t rt = (g_rgb_timer % (serial_count*step)) + space;
  const uint64_t lower = rt - step*fade;

  HSV hsv;

  for (uint8_t i = led_min; i < led_max; i++) {

    hsv.h = 0;
    hsv.s = 0;
    hsv.v = 0;

    uint8_t serial_in = 0; // the index of just the serial nodes, needed for math calculations

    // I don't like this n^2 loop but it seems to work fine
    for (uint8_t in = 0 ; in < count ; in++) { // index into ns for both serial and parallel nodes
      if (ns[in].parallel == PN_SER) {
        serial_in++;
      }
      if (ns[in].led_id == i) {
        uint64_t inrt = serial_in*step + space;
        if (lower < inrt && inrt <= rt) {
          hsv.h = ns[in].hue;
          hsv.s = ns[in].saturation;
          hsv.v = ((inrt - lower) * max_intensity) / (step*fade);
          break;
        }
      }
    }

    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

// LED ids can be found in keyboards/crkbd/rev1.c
path_node_t pn_numpad[] = {
  // 1-9
  { HV_BLUE, 20, PN_SER},
  { HV_BLUE, 15, PN_SER},
  { HV_BLUE, 12, PN_SER},
  { HV_BLUE, 19, PN_SER},
  { HV_BLUE, 16, PN_SER},
  { HV_BLUE, 11, PN_SER},
  { HV_BLUE, 18, PN_SER},
  { HV_BLUE, 17, PN_SER},
  { HV_BLUE, 10, PN_SER},

  // 0 in two places
  { HV_PURPLE, 9,  PN_SER},
  { HV_PURPLE, 22, PN_PAR},

  // the final two symbols
  { HV_GOLD, 8, PN_SER},
  { HV_GOLD, 7, PN_SER},

  // add some null nodes just for spacing
  { PN_BLACK },
  { PN_BLACK },
  { PN_BLACK },
  { PN_BLACK },
};

static bool animation_numpad(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  draw_path_nodes(pn_numpad, sizeof(pn_numpad)/sizeof(pn_numpad[0]), led_min, led_max);

  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
