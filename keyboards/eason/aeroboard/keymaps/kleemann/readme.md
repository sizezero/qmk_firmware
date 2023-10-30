
This is a revised readme for the Aeroboard 70. The default readme is
incorrect.

# aeroboard

A customizable hotswap 70% keyboard.

* Keyboard Maintainer: [EASON](https://github.com/EasonQian1)
* Hardware Supported: ab70lite
* Hardware Availability: [EASON](https://github.com/EasonQian1)

## First Time Building and Flashing

The stock PCB has been flashed with the VIA/Vial bootloader. For most
users, the easiest solution to customizing the keyboard will be to use
[Vial](https://get.vial.today/). These instructions are for replacing
VIA/Vial with QMK.

Note: these instructions were written with

    BOOTMAGIC_ENABLED = yes

set in `rules.mk`. Behavior may differ with a different setting.

Setup your QMK build environment and build the default keymap.

    make eason/aeroboard:default

In order to enable flashing you must have access to the reset button
on the bottom of your PCB, your PCB must be connected to the daughter
board via the ribbon cable, and your daughter board must be connected
to your compter via a USB cable. The easiest way to do this is to open
your keyboard case and flip your PCB upside-down so it lays flat just
in front of your keyboard. If your PCB already has
plate/switches/keycaps installed, you may want to lay the edges of the
plate on a couple books so that the switches don't depress. Double tap
the small reset button on the PCB using the small plastic tool that
comes with the keyboard. (or any small, non-metal tool) When you
perform a double tap, after a brief pause a USB drive should connect
to your computer.

Copy the generated `eason_aeroboard_default.uf2` file to the USB
drive. The keyboard will flash, the USB drive will disconnect, and the
keyboard will reconnect as a QMK keyboard.

## Followup Building and Consecutive Flashing

Once QMK is installed, bring up the USB bootloader drive in any of the
following ways:

* **Bootmagic reset**: Hold down Enter in the keyboard then replug
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the default keymap this is mapped to `F3`+`\`

You may continue to flash by copying the generated
`eason_aeroboard_default.uf2` file to the USB drive.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
