
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