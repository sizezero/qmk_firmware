# keyboardname

TODO: add the name of the keyboard above

TODO: link to an image of the keyboard 

![hotswap](https://i.imgur.com/kJzebgd.jpeg)
**Hotswap PCB**

A 40% keyboard.

* Keyboard Maintainer: [Sean R. O'neill](TODO: Sean's github repo https://github.com/qmk)
* Hardware Supported: TODO
* Hardware Availability: TODO

Make example for this keyboard (after setting up your build environment):

    make oneillseanr/keyboardname:default

Flashing example for this keyboard:

    make oneillseanr/keyboardname:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

TODO: rewrite this when we figure out how the bootloader works.

Enter the bootloader in 3 ways:

* **Keycode in layout**: Using the default firmware, assign a key to Reset (`QK_BOOT`) and press the assigned key.
* **Physical reset button**: Briefly press the button on the back of the PCB

The QMK default keymap has FN+Backspace assigned to `QK_BOOT` so you can use that key sequence for subsequent flashing.
