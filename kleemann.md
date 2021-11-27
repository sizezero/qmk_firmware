
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

    make kbdfans/kbd75/rev2:kleemann
    make kbdfans/kbd75/rev2:kleemann:flash

I was able to reset it with the original factory rest of
SCRLK+Backspace. Hold both keys plug in, wait a bit, watch
`ATm32u4DFU` show up in `sudo dmesg -w`, and then release. This worked
for me with the initial bootloader but after flashing, my new keymap
(FN+ESC) it failed to work. It seems the new behavior with the
reflashed QMK is to plug in the keyboard first, then hold the reset
combo to get into flash mode. I threw in a bunch of reset codes into
the keyboard layout including CapsLock+ESC, ScrollLock+ESC,
LeftSpace+ESC, and MiddleSpace+ESC. If I every accidentally hit one of
these keys it won't accidentally reset the keyboard, it will just mean
I have to unplug and replug the keyboard to get it back. If it happens
accidentally in practice I might want a more obscure reset option.

# Building the Original Project

Here are the orignal steps for cloning the project:

    <clone qmk project in github>
    git clone https://github.com/sizezero/qmk_firmware.git
    git remote add upstream https://github.com/qmk/qmk_firmware.git
    git remote -v
    git branch kleemann
    git checkout kleemann
    git push -u origin kleemann
