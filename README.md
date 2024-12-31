# 2dgameenginec-
A 2D game engine written in c++

This was written whilst following a course/experimenting on my own.

Libs you'll need downloaded:\
SDL2\
SDL2_image\
SDL2_mixer\
SDL2_ttf\
gml\

These must be downloaded and installed globally (there's a bunch of header in the `/libs` that I need to remove but will do as project grows).

To build this locally follow these steps:

To generate a compile_commands.json folder (this is needed for clang to recognise your file structure)\
run: `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .`

To build cmake\
run: `cmake --build .`\
from the project root

then run: `make`

and to launch \
run: `./bin/2dgameengine` 

Just playing around on linux at the moment and this is the barebones way to build/run this engine.\
I will expand on it over time (or that's the plan, at least)
