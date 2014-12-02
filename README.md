This is an attempt to make a game engine from (almost) scratch using OpenGL for rendering and GLFW for managing the OpenGL context and window creation. The end goal of this engine is to create a game, although it will be designed to be a game engine suitable for general use. It currently has the following dependencies:

[*] GLFW (OpenGL Context/Window Creation)
[*] GLEW (Works with GLFW to manage OpenGL)
[*] GLM (Mathematics)
[*] tinyobjloader (Loading OBJ and MTL files)
[*] SOIL (Loading texture images)

These dependencies have repositories linked in submodules under the deps directory. There are also plans to use bullet as a physics library, although it is also planned to remove GLM and bullet for math and physics libraries writted to work with the game engine and to be suitable for general simulation use. These will be written when the game engine is in a usable, stable state. It is also planned to switch from OBJ/MTL models to some type of binary format for maps and models.

This engine will be written to be compatible with Linux, Mac OS X, and Windows. Future modifications will possibly be written to support mobile platforms with OpenGL ES and work to provide PlayStation support. DirectX support may also be written at some point to better support Windows and lead to the possibility for XBox support.

The engine uses the CMake build system and is regularly written on a system using Ubuntu 14.10 with proprietary nVidia drivers and using gcc for compilation, so all commits should be compatible with such a system. Mac OS X is also used at times using both gcc and clang. Commits are not tested on Windows at this time, but will be in the near future.
