GameOfLife
----------

In this project, we implement Conway's Game of Life (see the [link](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life))
using different parallelising techniques. We have implemented a serial solution which can be speed up using OpenMP. We
are also working on parallelising the project with OpenMPI, and OpenCL (but these two options are not ready yet). The
game needs a Life 1.06 file to start the evolution, and saves the different steps in the same format. A Python script
(using Matplotlib) is provided to make a video out of the different Life files created by the game.

Credit goes to [MattClarkson](https://github.com/MattClarkson) for the CMake template used for this package. 

Note: The project is not finished yet, but depending on my free time it might be finished soon.

Overview
--------

The features of the project are:
 1. It utilises and produces Life 1.06 files (a lot of them can be found at this [link](http://conwaylife.com/wiki/Category:Patterns)).
 2. Uses OpenMP to speed up the evolution.
 3. Will use (eventually) OpenMPI and OpenCL.
 4. Python script to make a video out of the frame files created by the game.
 5. A script to compare the scaling of the serial solution and the one parallelised with OpenMP.

Tested On
-----------------------------

 * Windows - Windows 10, g++ 5.3.0 (MinGW - MSYS), CMake 3.7.1, Boost 1.63.0, no SuperBuild
 * Linux - Ubuntu 16.04 LTS , g++ 5.4.0 , CMake 3.5.1, Boost 1.56.0, with SuperBuild


Configure CMakeLists
-----------------------------

This project comes with the possibility of downloading several libraries.
In particular, it is possible to download and build Boost, which is needed
for the project to work. To download and build dependencies, use
CMake to configure:

  * BUILD_SUPERBUILD:BOOL=ON

You can also avoid to download and build these dependencies, in case they
are already present in your host machine. In that case, set:

  * BUILD_SUPERBUILD:BOOL=OFF

In any case, the following options should be set as follow:

  * BUILD_Boost:BOOL=ON

To switch between static/dynamic linking, use CMake to set:

  * BUILD_SHARED_LIBS:BOOL=ON|OFF

To switch between Debug and Release mode, use CMake to set:

  * CMAKE_BUILD_TYPE:STRING=Debug|Release

Note: Only Debug and Release are supported. 

If you do not set the SuperBuild flag ON, you will need to check the version
of your Boost libraries. Indeed, it might be possible that your host system
have a version of Boost that is different from the one assumed here (1.56.0).
In that case, you will have to modify the ./CMakeLists.txt file (replace 1.56
with your version number in line 238).


Build Instructions
-----------------------------

Once you have configured the CMakeLists.txt file with your favourite options,
you can build the package. Here an example of how you can build it in Linux
(and MacOS). Write in the terminal the following commands

```
mkdir Build
cd ./Build/
cmake ..
```

If the output of cmake is positive, write ```make``` to build the package.

To test the package, use ```make test```.


Windows Users
-------------

If you build the project with shared libraries (BUILD_SHARED_LIBS:BOOL=ON)
then when you run executables, you should look for the batch file
StartVS_Debug.bat or StartVS_Release.bat in the LEASTSQUARESPACKAGE-build folder.
This sets the path before launching Visual Studio, so that dynamically
loaded libraries are found at run time.

Note: The package was never built with Visual Studio, so other problems might appear.


Command-line application
------------------------

The project comes with a command-line application that takes as input a seed (a Life 1.06
file with the initial configuration of the frame) and return a series of Life 1.06 files,
each of them with the frame updated one time step further. The application also needs a
configuration file ```config.dat``` with the following items,

 * ```number_of_x_cells``` : the length of the frame in the x direction
 * ```number_of_y_cells``` : the length of the frame in the y direction
 * ```time_steps``` : the number of time steps we want to evolve the game
 * ```output_filename``` : name of the output Life 1.06 files
 * ```extension``` : extension of the output Life 1.06 files (suggested one is life)

The configuration file is passed to the application with the option ```-c```.
The application also produce a yaml configuration file which can be used for
running the Python script building the video. 
