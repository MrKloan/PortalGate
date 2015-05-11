#include "includes.h"

Keyboard *KeyboardHandle(Keyboard *this)
{
    if(this->keys[27])
        quit(0);

    //Camera
    if(this->keys['z'])
        camera->forward(camera);
        //camera->lookUp(camera);
    if(this->keys['s'])
        camera->back(camera);
        //camera->lookDown(camera);
    if(this->keys['q'])
        camera->left(camera);
        //camera->lookLeft(camera);
    if(this->keys['d'])
        camera->right(camera);
        //camera->lookRight(camera);
    if(this->keys['a'])
        camera->up(camera);
    if(this->keys['e'])
        camera->down(camera);

    //Cube
    if(this->keys[KEY_UP] && !cube->moving)
    {
        cube->moving = 1;
        cube->move[CUBE_FORWARD] = 1;
    }
    if(this->keys[KEY_DOWN] && !cube->moving)
    {
        cube->moving = 1;
        cube->move[CUBE_BACK] = 1;
    }
    if(this->keys[KEY_LEFT] && !cube->moving)
    {
        cube->moving = 1;
        cube->move[CUBE_LEFT] = 1;
    }
    if(this->keys[KEY_RIGHT] && !cube->moving)
    {
        cube->moving = 1;
        cube->move[CUBE_RIGHT] = 1;
    }

    return this;
}

Keyboard *NewKeyboard(void)
{
    int i;
    Keyboard *this = malloc(sizeof(Keyboard));

    this->handle = KeyboardHandle;

    for(i = 0 ; i < 260 ; i++)
        this->keys[i] = 0;

    return this;
}
