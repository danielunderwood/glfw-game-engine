__Current Status:__ Work on this project has been discontinued in favor of using a commercial engine due to lack of time to fully develop an engine. I have noticed that several people have shown interest in this project; if anyone would like to continue working on this project, I would be glad to contribute ideas and guidance. The engine is still in need of several components, most notably materials and physics systems. Due to a lack of artistic knowledge, the materials system is one of the reasons for discontinuing the project. Skeletal and animation systems are needed as well. Feel free to fork the project to continue on it on your own, but it would likely be better to continue the project from here with community contributions. If anyone is interested in continuing the project as a community effort, please leave a comment on the commit for the change of README.md or contact me via email (can be found in git log).

Build Status: [![Build Status](https://api.travis-ci.org/danielunderwood/glfw-game-engine.svg "Build Status")](https://travis-ci.org/danielunderwood/glfw-game-engine)

This is an attempt to make a game engine from (almost) scratch using OpenGL for rendering and GLFW for managing the OpenGL context and window creation. The end goal of this engine is to create a game, although it will be designed to be a game engine suitable for general use. It currently has the following dependencies:

+ GLFW (OpenGL Context/Window Creation)
+ GLEW (Works with GLFW to manage OpenGL)
+ GLM (Mathematics)
+ tinyobjloader (Loading OBJ and MTL files)
+ SOIL (Loading texture images)


These dependencies have repositories linked in submodules under the deps directory. There are also plans to use bullet as a physics library, although it is also planned to remove GLM and bullet for math and physics libraries writted to work with the game engine and to be suitable for general simulation use. These will be written when the game engine is in a usable, stable state. It is also planned to switch from OBJ/MTL models to some type of binary format for maps and models.


It is planned to write interface layers for various libraries used. This will allow anyone to easily switch which library is used for a specific part of the code (physics, math, etc.), or even use different libraries for different functions in one area. This can allow performance improvements or let anyone using this library choose dependencies available for their chosen platform or with favorable license terms.


The engine is currently written in C++. At some part in the future, scripting support will be added for at least Lua and possibly other languages with python being a strong contender.


This engine will be written to be compatible with Linux, Mac OS X, and Windows. Future modifications will possibly be written to support mobile platforms with OpenGL ES and work to provide PlayStation support. DirectX support may also be written at some point to better support Windows and lead to the possibility for XBox support.


The engine uses the CMake build system and is regularly written on a system using Ubuntu 14.10 with proprietary nVidia drivers and using gcc for compilation, so all commits should be compatible with such a system. Mac OS X is also used at times using both gcc and clang. Commits are not tested on Windows at this time, but will be in the near future.
