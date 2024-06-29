# KB-40-A

![KB-40-A illustration](https://i.imgur.com/x8FNkei.png)

A compact, staggered, 40% (4x12) keyboard. More info at [TODO](TODO)

* Keyboard Maintainer: [Sean O'Neill](https://github.com/billowybrimstone)
* Hardware Supported: TODO
* Hardware Availability: TODO

Make example for this keyboard (after setting up your build environment):

    make aokay/kb40a:default

Flashing example for this keyboard:

    make aokay/kb40a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

TODO: rewrite this when we figure out how the bootloader works.

Enter the bootloader in 3 ways:

* **Keycode in layout**: Using the default firmware, assign a key to Reset (`QK_BOOT`) and press the assigned key.
* **Physical reset button**: Briefly press the button on the back of the PCB

The QMK default keymap has FN+Backspace assigned to `QK_BOOT` so you can use that key sequence for subsequent flashing.
