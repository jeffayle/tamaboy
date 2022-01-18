# tamaboy

tamaboy is a [Tamagotchi v1](http://adb.arcadeitalia.net/?mame=tama) emulator
for Gameboy Advance based on [TamaLIB](https://github.com/jcrona/tamalib/).

## Usage

The Tamagotchi's Left, Middle and Right buttons are mapped respectively to the
d-pad Left, UpDown and Right.

The same buttons are also mapped to Select, A and B respectively. This mapping
is intended to be as intuitive as possible to navigate the device's menus.

Normally only the dot-matrix "pixels" are shown on screen. The eight lcd icons
normally above and below the dot-matrix display are displayed as on overlay when
needed.

Press and hold the start button to show the lcd icon overlay. The overlay is
shown for 3 seconds when an icon changes. Press start to dismiss.

NB: Make sure to set the clock or your egg will never hatch. There should be
animated arrows on the clock screen.

*Do not* shut off your Gameboy or your Tamagotchi will die.

## Compile Time Dependencies

- gba-dev from [devkitPro](https://devkitpro.org/wiki/Getting_Started)
- python3 and pillow (`pip3 install pillow`)
- a tamagotchi rom (the file named `tama.b` from the MAME romset `tama.zip`)

## How to Compile

Place the rom in this directory with the name `tama.b`. This file should be
12288 bytes.

Run the command `make`.

The otput file `tamaboy.gba` is a standalone Gameboy Advance multiboot image
that contains the tamaboy emulator and the provided rom file.
