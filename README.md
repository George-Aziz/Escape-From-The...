# LearnOpenGL.com code repository
Contains code samples for all tutorials of [https://learnopengl.com](https://learnopengl.com). 

## Windows building
All relevant libraries are found in /libs and all DLLs found in /dlls (pre-)compiled for Windows. 
The CMake script knows where to find the libraries so just run CMake script and generate project of choice.
Note that you still have to manually copy the required .DLL files from the /dlls folder to your binary folder for the binaries to run.

Keep in mind the supplied libraries were generated with a specific compiler version which may or may not work on your system (generating a large batch of link errors). In that case it's advised to build the libraries yourself from the source.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev  libxi-dev` .
Next, run CMake (preferably CMake-gui). The source directory is LearnOpenGL and specify the build directory as LearnOpenGL/build. Creating the build directory within LearnOpenGL is important for linking to the resource files (it also will be ignored by Git). Hit configure and specify your compiler files (Unix Makefiles are recommended), resolve any missing directories or libraries, and then hit generate. Navigate to the build directory (`cd LearnOpenGL/build`) and type `make` in the terminal. This should generate the executables in the respective chapter folders.

Note that CodeBlocks or other IDEs may have issues running the programs due to problems finding the shader and resource files, however it should still be able to generate the exectuables. To work around this problem it is possible to set an environment variable to tell the tutorials where the resource files can be found. The environment variable is named LOGL_ROOT_PATH and may be set to the path to the root of the LearnOpenGL directory tree. For example:

    `export LOGL_ROOT_PATH=/home/user/tutorials/LearnOpenGL`

Running `ls $LOGL_ROOT_PATH` should list, among other things, this README file and the resources direcory.

## Mac OS X building
Building on Mac OS X is fairly simple (thanks [@hyperknot](https://github.com/hyperknot)):
```
brew install cmake assimp glm glfw
mkdir build
cd build
cmake ../.
make -j8
```

## Glitter
Polytonic created a project called [Glitter](https://github.com/Polytonic/Glitter) that is a dead-simple boilerplate for OpenGL. 
Everything you need to run a single LearnOpenGL Project (including all libraries) and just that; nothing more. 
Perfect if you want to follow along with the tutorials, without the hassle of having to manually compile and link all third party libraries!


### How to Run the Game
To run the game simply build the project firstly as stated above
After building has been done do ``cd bin/CG_Assignment`` 
Once in the directory to execute and run the game do ./CG_Assignment__game

### How to Play The Game
This game is similar to a game called Slender Man where the player must escape an enemy whilst being chased by it
In this case the enemy is a big monster which looks like a Minecraft Creeper
The enemy only starts to move towards the player at the moment, the torch besides the player on the ground is picked up
The objective of the game is to escape the enemy by looking for hammers around the map where there is a total of 5
Once all 5 hammers have been obtained, the player must go to the man standing besides the portal where then the player must press the <G> key
Once the <G> key has been pressed the entry to the portal besides the player will be opened through a small animation and the player must quickly enter it to win

All Ground Loot/ Pick-up items are automated i.e. The player can simply walk over them to pick up.

There are multiple keyboard inputs that can be found below:
- <O> Makes the world very bright without the need of a torch
- <L> & <K> Decrease/Increase torch brightness radius
- <G> Gives hammers to man standing besides portal (Must be close to the man)
- <P> Toggle a different projection type into Orthographic or Perspective depending on which projection is current active

In addition to the keyboard inputs, you can use the mouse to look around

**NOTE: In addition to the game found in CG_Assignment, there are also other files that are completed LearnOpenGL Tutorials**
