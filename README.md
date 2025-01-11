# 2dgameenginec-

A 2D game engine written in c++

Libs you'll need downloaded:\
SDL2\
SDL2_image\
SDL2_mixer\
SDL2_ttf\
gml

These must be downloaded and installed globally (there's a bunch of headers in the `/libs` that I need to remove but will do as project grows).

To build this locally follow these steps:

Make a build dir
run: `mkdir build`

Enter build
run: `cd build`

To build cmake\
run: `cmake ..`\
from the build dir

then run: `make`

and to launch from build dir \
run: `./bin/2dgameengine`

Just playing around on linux at the moment and this is the barebones way to build/run this engine.\
I will expand on it over time (or that's the plan, at least) \

TODOS:

- Come up with a better way to assign Props their unique names
  as currently it's bloating the individual prop classes
- Make the scripts map in Director take strings as the key
  and then you can pass constants instead of passing a class
- Create the constant names for each Prop class within each class
  like: string TRANSFORM_CLASS = "TransformClass" to avoid
  typing mistakes
- Not handling cleaning up the prop stores, need to sort that
