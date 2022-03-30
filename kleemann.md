
# Robert's dz60

I've got a dz60 with a keymap and I'm using this branch of the QMK
project to build and flash it onto my keyboard. It seems Windows and
Mac users have a slick UI but linux is stuck on the command line. I
tried the qmk command line app for a bit but it seemed a little
mysterious. I think it's safer to have a local fork of the project,
then I can tag working versions and update it when I feel like it.

# QMK Configurator

This is the web interface that allows you to make keyboard layouts. I
can't see a reason _not_ to use this. It produeces `.json` files but
can also compile `.hex` files that are eventually flashed. It's good
enough for me to create a `.json` file and then compile to `.hex`
myself. Place the `.json` file here:

    keyboards/dz60/keymaps/kleemann/keymap.json

# Dependencies

The more recent builds of the source tree seem to need and external qmk program.

From the [full instructions](https://beta.docs.qmk.fm/tutorial/newbs_getting_started):

    sudo apt install -y git python3-pip
    python3 -m pip install --user qmk
    cd ~/bin
    ln -s ../.local/bin/qmk qmk

# Building and Flashing

Once:

    make git-submodules

Whenever:

    make clean
    make dz60:default
    make dz60:kleemann

Plug in the keyboard and press the button in the bottom with a paper
clip for a few seconds.

    make dz60:kleemann:flash

This should immediately update the keyboard at which point you can use
the keyboard to type into the computer.

Instead of the paper clip you could also use the reset button
(middlespace + backspace + ESC) but I haven't tried that yet. I think
you have to do the sequence before plugging the keyboard in.

# KBD75

The build for the KBD75 is similar.

    make clean
    make kbdfans/kbd75/rev2:kleemann

The KBD75 needs the case removed to access the reset button so it's easier to use a keystroke to reset. First:

    sudo dmesg -w

Then middle space + ESC. You should see `ATm32u4DFU` up in the dmesg output.

    make kbdfans/kbd75/rev2:kleemann:flash

# Contra 40%

The Contra uses a Pro Micro or Sea Micro as the controller. This
requires the caterina bootloader but this appears to be all setup in
the contra/ keyboard project. There are multiple ways to reset it:

- Short the ground and reset. Reset appears to be the third pin the the left of the usb port. I'm not sure about ground.
- Press the reset button on the sea micro. Some people say you need to press it twice.
- Press the reset button the PCB after it is socketed.
- Configure the layout with a reset code.

Here's what the Sea Micro looks like. Reset button doesn't seem to change what it displays.

    [33157.731843] usb 3-4: new full-speed USB device number 7 using xhci_hcd
    [33157.882061] usb 3-4: New USB device found, idVendor=03eb, idProduct=2ff4, bcdDevice= 0.00
    [33157.882070] usb 3-4: New USB device strings: Mfr=1, Product=2, SerialNumber=3
    [33157.882073] usb 3-4: Product: ATm32U4DFU
    [33157.882075] usb 3-4: Manufacturer: ATMEL
    [33157.882077] usb 3-4: SerialNumber: 1.0.0

I made a very simple layout with two layers. The reset is the lower
right key plus the upper left key. Lower right key can be tested by
pressing various top row keys to produce fn keys.

    make clean
    make contra:kleemann
    make contra:kleemann:flash

The flash did not recognize the controller. It seems that the Contra
is configured to look for the Pro Micro which is very different than
the Sea Micro. Changing the bootloader seemed to flash it and get it
to be recognized

There is both a kleemann layout and a test layout. The test layout is
simpler and good at verifying PCB connection and switches.

# Building the Original Project

Here are the orignal steps for cloning the project:

    <clone qmk project in github>
    git clone https://github.com/sizezero/qmk_firmware.git
    git remote add upstream https://github.com/qmk/qmk_firmware.git
    git remote -v
    git branch kleemann
    git checkout kleemann
    git push -u origin kleemann

# Home Row Mods

There is a whole thing about doing [home row mods.](https://precondition.github.io/home-row-mods) The gist is that you set your home keys to mod tap keys so that long press acts like the mod and tap acts like the home row letter.

It turns out you can't just do this and have your keyboard work. There will be lots of mistyped keys as single presses are sometimes interpreted as mods and long presses are sometimes interpreted as characters. The solution is to set a bunch QMK compile flags that change how keypresses are interpreted.

There are lots of options but right now I'm starting with just a few:

    #define IGNORE_MOD_TAP_INTERRUPT
    #define PERMISSIVE_HOLD
    #define RETRO_TAPPING

These settings can be in many different places but I've put them in `keymaps/<keymapname>/config.h`

Right now I'm only testing this on my writing keyboard. If it works well I'll move them to my work keyboard as well.

## March 2022

I've been having a bunch of mis-types. I'm going to try a couple tweaks.

### 1

The tapping term is the maxximum time that a key should be held to register. This is used a lot for Tap and Hold settings and it's best visualized in the following diagram:

https://cdn.discordapp.com/attachments/663573863480950808/757162393209012304/modtap.pdf

TAPPING_TERM is used to define the differences between presses, holds, and other actions. It basically represents the longest time period that a key would be normally pressed. PERMISSIVE_HOLD sets an infinite tapping term so it really shouldn't be used. It is much better to customize the tapping term based on your own personal typing style.

So what is the correct value for typing term? The default is 200MS. Most people choose a value between 150MS and 220MS. Higher values of tapping term will result in accidental alphas and lower values will result in accidental mods. It is easiest to troubeshoot by setting the default to the high side, and then lowering it until there are no problems. The default tapping term needs to be built into the config.h but the modifications occur by assigning DT_PRINT, DT_UP, AND DT_DOWN to extra keys. I'll be assigning them as the bottom leftmost keys on the space mod layer: DOWN, UP, PRINT. rules.mk also needs a DYNAMIC_TYPING_TERM_ENABLE = yes.

To test this, first try long strings of lower case letters then practice on text containing capital letters. If you get accidental characters, lower the typing term and not the new value.



### 2

I was bugged that holding down a LT for a while and then releasing it acted as a keypress. It turns out that I had enabled this annoying behavior with  RETRO_TAPPING. I got rid of it.
