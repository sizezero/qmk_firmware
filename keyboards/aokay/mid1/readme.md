# KB-40-A

![KB-40-A illustration](https://i.imgur.com/x8FNkei.png)

## Description

A compact, staggered, 40% (4x12) keyboard.

* Keyboard Maintainer: [Sean O'Neill](https://github.com/oneillseanm)
* Hardware Supported: TODO
* Hardware Availability: TODO

## Setup

Make example for this keyboard (after setting up your build environment):

    make aokay/mid1:default

Flashing example for this keyboard:

    make aokay/mid1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in two ways:

* **Keycode in layout**: Using the default firmware, press `FN+Backspace` which is assigned to `QK_BOOT`.
* **Physical reset button**: Briefly press the button on the front of the PCB
