MOUSEKEY_ENABLE = no    # Mouse keys

# I think matrix supercedes the others so you only want one of these
# enabled
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes

OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes

# kleemann's custom stuff

# Elite C v4 needs DFU Bootloader
BOOTLOADER = atmel-dfu

# needed for custom animation
RGB_MATRIX_CUSTOM_USER = yes

# load the old keymap.c
SRC += default.c
