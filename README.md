# TempleRun 
### 3D arcade game in OpenGL

The goal of this project was to create a 3D arcade game looking like TEMPLE RUN using the OpenGL library.

## Required libraries
Make sure that you have GLEW, cmake, eigen, SDL, SDL_ttf, SDL_image and SDL_mixer installed. If your on Debian or Ubuntu, you can install packages:
```
sudo apt-get install build-essential cmake libeigen3-dev libglew-dev libsdl-image1.2 libsdl-image1.2-dev libsdl-ttf2.0-0 libsdl-ttf2.0-dev libsdl-mixer1.2 libsdl-mixer1.2-dev doxygen 
```

## Compile and launch the game

To compile the game and the libreries, use the `CMakeLists` file in a build folder:
```
mkdir build
cd build
cmake ../
```
Then, use the `makefile` to compile :
```
make
```

Finally, to start the game, simply run the command:
```
./bin/TEMPLE_RUN_main
```
To display the Menu, run the command : 
```
./bin/TEMPLE_RUN_menu
```
To display the Level Menu, run the command : 
```
./bin/TEMPLE_RUN_levelMenu
```
## Commands

Now that you started the game, the game character in running, here are the instructions to play : 

* To jump : Press "Z" or "Space Key" or "Up key".
* To move or turn left : Press "Q" or "Left Key".
* To move or turn right : Press "D" or "Right Key".
* To change from Character's view to General view : Press "C".
* To be able to control the camera by turning around the character in General view : Press "V".

## Documentation

To see the documentation, open the file `doc/html/index.html` with with your favorite browser.

### A 3D arcade game created by Amina FADILI, Cécile ROUSSET and Nicolas SENECAL
