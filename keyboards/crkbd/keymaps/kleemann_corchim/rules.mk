MOUSEKEY_ENABLE = no    # Mouse keys

# I think matrix supercedes the others so you only want one of these
# enabled
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = no

OLED_ENABLE     = yes
OLED_DRIVER     = ssd1306
LTO_ENABLE      = yes

# kleemann's custom stuff

# Elite C v4 needs DFU Bootloader
BOOTLOADER = atmel-dfu

# start without any custom code
#SRC += default.c

BOOTLOADER = rp2040
CONVERT_TO = promicro_rp2040

