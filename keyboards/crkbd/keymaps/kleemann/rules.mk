MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = no
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes

# kleemann's custom stuff

# Elite C v4 needs DFU Bootloader
BOOTLOADER = atmel-dfu

# load the old keymap.c
SRC += default.c
