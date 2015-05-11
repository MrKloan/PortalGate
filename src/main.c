#include "includes.h"

void quit(int status)
{
    display->running = 0;

    sounds->free(sounds);
    pillars->free(pillars);
    turrets->free(turrets);
    tiles->free(tiles);
	cube->free(cube);
	stargate->free(stargate);
    display->free(display);
    skybox->free(skybox);
	free(camera);

	exit(status);
}

unsigned char file_exists(char *path)
{
    FILE *file;

    if((file = fopen(path, "rb")))
    {
        fclose(file);
        return 1;
    }
    else
        return 0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    camera      = NewCamera(0, 0);
    display     = NewDisplay(&argc, argv, 0);
    stargate    = NewStargate();
    cube        = NewCube();
    turrets     = NewArray();
    pillars     = NewArray();
    tiles       = NewArray();
    sounds      = NewSoundManager(&argc, argv, "data/sounds/");
    skybox      = NewSkybox();

    generateTurrets();
    generatePillars();
    generateTiles();
    sounds->load(sounds);

    display->start();
	return 0;
}
