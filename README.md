# PANG/PS2 

a remake of the old arcade ball game Pang for Playstation 2 

Last update: January 12, 2006

![](https://archive.org/download/pang_ps2_bin_20060112/IMG_0489.JPG)

Copyright (C) 2005 michel louvet
http://michel.louvet.club.fr/index.html

Playstation 2 version by Olivier "evilo" Biot & [The Froggies](http://psxdev.org)

History
-------

01-12 : Fixed Protection Bonus
	Fixed blocking balls (from version 1.20)

01-09 : first version
	based on original 1.0 version
	

Compiling:
----------

To get your sources compiled, checkout the latest PS2SDK source tree. 
You will need SDL, SDL_mixer, SDL_image. 
All of these are available at www.ps2dev.org 


Enhancements/Modifications :
----------------------------

- Added Joypad support through SDL
- cleaned-up/remade sound code (SDL Mixer)
- Added several flags (all used for the PS2) 
- ENABLE_JOYSTICK : added Joypad support through SDL (original use keyboard only)
- EMBEDDED_FILES : .wav & .bmp are embedded into the executable ELF
- USE_VSYNC	: orginal version use SDL_Delay()

Credits:
--------
michel louvet for sharing it's source code.
gawd for the SDL library port on the ps2.