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

- Not using memory arena correctly, should have one arena for entities,
  an arena for each prop, so 'TransformPropArena', and an arena for each script too
  this way you're managaging the lifetimes better
- Anywhere we're using a string as a key in a map, change to a typeid
  and just pass that typeid as an argument
- Not handling cleaning up the prop stores, need to sort that with an arena
- append member methods and variables with 'm' instead of using 'this'
