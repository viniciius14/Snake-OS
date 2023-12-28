# Snake-OS

![screenshot](docs/resources/Snake_sc_1.png)

This techically is a ring 0 kernel but Snake-OS much sounds better.
If you'd like to read up on how it works theres Notes.md file [here](https://github.com/viniciius14/Snake-OS/blob/main/docs/Notes.md).

#### Features:
- 32-bit (x86)
- Fully custom bootloader
- Simple keyboard driver
- Simple graphics driver
- Snake game

#### Resources
- [osdev.org wiki](https://wiki.osdev.org/Main_Page)
- [James Molloy's Kernel Development Tutorials](http://www.jamesmolloy.co.uk/tutorial_html/)
- [osdever tutorials](http://www.osdever.net/tutorials/view/interrupts-exceptions-and-idts-part-1-interrupts-isrs-irqs-the-pic)
- [Queso Fuego Youtube Channel](https://www.youtube.com/@QuesoFuego)
- [Daedalus Community Youtube Channel](https://www.youtube.com/@DaedalusCommunity)

### Building & Running
**NOTE**: This has only been tested with the QEMU emulator.

To get all essential software (like the cross compiler) run the SETUP.sh, if the script is not compatible with your Linux distro I'd suggest following the link in the file to check the other version of SETUP.sh.
```
$ . SEPUP.sh
```
After having all the necessary tools installed (which may take a while) do:
```
$ cd src
$ . run.sh
```

Running with WSL on Windows also works.


### Other
This project was innitally inspired by [jdh's tetris OS](https://youtu.be/FaILnmUYS_U) video from which I decided to try making my own version around the same concept.