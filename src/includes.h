#ifndef INCLUDES
#define INCLUDES

///Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
///OpenGL
#include <GL/glut.h>
///SOIL
#include <SOIL/SOIL.h>
///assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
///OpenAL
#include <AL/alut.h>

#define PI 3.14f

///Custom
void quit(int);
unsigned char file_exists(char*);

#include "Array.h"
#include "AABB3D.h"
#include "Skybox.h"
#include "Tile.h"
#include "Stargate.h"
#include "Cube.h"
#include "Turret.h"
#include "Pillar.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Display.h"
#include "Sound.h"

Display      *display;
Skybox       *skybox;
Camera       *camera;
Cube         *cube;
Stargate     *stargate;
Array        *turrets;
Array        *pillars;
Array        *tiles;
SoundManager *sounds;

#endif
