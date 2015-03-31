**SNE** is a cross platform experimental 3D gaming engine.

Some facts about the engine:
  * The engine is written 99% in C++ and the game development can be done in C++ or Lua.
  * The native engine resource definition format is xml but later other formats will be also implemented.
  * Currently iOs and Windows variants are in development. When a more or less usable version for iOs and Windows will be ready the Android version will be also implemented.
  * By design the code which uses the engine in C++ and Lua plus all the resources(textures, vb,ib,...) excluding shaders are portable. The shaders must be written separately for each platform.


Features which are currently in active development:
  * engine lua support
  * engine bullet physics support
  * rendering materials
  * blender exporter for the engine

The 3 rules of the sasha-noob-engine design:
  * The sasha-noob-engine may not injure the human pride due to its code complexity, or  allow a human being to come to harm due to it's usability issues.

  * The sasha-noob-engine must be fast as orders given to it by human beings, except where such orders would conflict with the First Law.

  * The sasha-noob-engine must protect it's cross platform consistency as long as such protection does not conflict with the First or Second Laws.

Current Restrictions:

It is designed to support platforms with minimum OpenGL ES 2.0 functionality.
Open GL 1.x will not be supported.

The project is in a very early development stage and to many things are still partially implemented or not implemented at all.




**Info**:
  * [Currently supported lua API](lua_api_ref.md). Not a final version.

**Some Simple Examples of how to use the engine:**
  * [ex0: Hello Torus World](HelloWorldApplication.md)
  * [ex1: Lua snail shell mesh](ex1LuaMesh.md)


Browse the engine [source code](http://code.google.com/p/sasha-noob-engine/source/browse)

## Last Updates: ##

  * 5/03/2012 The engine is able to run also on windows.
> > Ex1: Lua snail shell mesh running on windows:
> > ![http://wiki.sasha-noob-engine.googlecode.com/git/engine-on-windows.png](http://wiki.sasha-noob-engine.googlecode.com/git/engine-on-windows.png)

  * 6/02/2012 The export from blender for solid materials objects and rendering in the engine is working.


> Example:

  * The world created and rendered in blender:

> ![http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render.png](http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render.png)

  * The world exported from the blender and rendered in the engine using a simple shader:

> ![http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render_simple.png](http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render_simple.png)

  * The world exported from the blender and rendered in the engine using per pixel lighting shader:

> ![http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render_pixel.png](http://wiki.sasha-noob-engine.googlecode.com/git/test_blender_render_pixel.png)
