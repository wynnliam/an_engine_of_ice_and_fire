# An Engine of Ice and Fire
A tile-based 2D top down C++ game engine that employs the SDL 2 library and object oriented practices I learned from CS 202.

This is the bare-bones code for An Engine of Ice and Fire.

It supports tiles, levels, actors, and simple UI features.
Very soon I will add support for sounds.

Specifically, what you will find are as follows:
-Tiles
-Levels
	-Level streaming (that is, being able to go to different levels)
-Actors
	-Characters
		-A simple player
		-A simple AI character
	-Props that are interactive
	-Particles
	-Items
		-Shields
		-Weapons (Note that while they will fire, the input handling needs to be implemented)
			-Projectile
			-Tracer
			-Melee
-Simple UI

# Required Packages

To use this, you must have the following packages:

1. SDL 2
2. SDL 2 Image
3. SDL 2 Mixer
4. SDL 2 TTF

A quick google search should show you how to get those.

# To Compile

Simply run:

```
> make clean all
> cd bin/
> ./a.out
```

Note that individual classes can be compiled so that you needn't recompile the entire project once a small change is made.

# How to use AEOIAF

Once you run it, you will be confronted by a red screen. This does not mean an error. It is a placeholder for a company logo
and/or some other introduction. Simply press ESC and you will reach the main menu. There is a little box that says PLAY in
the middle of the screen. Press that and you will be in the game! You can walk around and... thats it. There are two little circular
objects in the world. You can press E when you mouse is over them and they are removed from the level. A little AI character
will follow use. If you press E when looking at the brown rectangle, you will go to a different level.
