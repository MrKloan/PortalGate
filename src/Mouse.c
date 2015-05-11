#include "includes.h"

Mouse *MouseClick(Mouse *this)
{
    if(this->state[MOUSE_LEFT])
    {
        float absX = abs(this->x - this->px);
        float absY = abs(this->y - this->py);

        if(absX != 0.f && absY != 0.f)
        {
            if(absX > absY)
            {
                if(this->px > this->x)
                {
                    if(camera->invertX)
                        camera->lookRight(camera);
                    else
                        camera->lookLeft(camera);
                }
                else if(this->px < this->x)
                {
                    if(camera->invertX)
                        camera->lookLeft(camera);
                    else
                        camera->lookRight(camera);
                }
            }
            else
            {
                if(this->py < this->y)
                {
                    if(camera->invertY)
                        camera->lookUp(camera);
                    else
                        camera->lookDown(camera);
                }
                else if(this->py > this->y)
                {
                    if(camera->invertY)
                        camera->lookDown(camera);
                    else
                        camera->lookUp(camera);
                }
            }
        }
    }

    return this;
}

Mouse *MouseMove(Mouse *this)
{
    return this;
}

Mouse *NewMouse(void)
{
    Mouse *this = malloc(sizeof(Mouse));

    this->inWindow = 1;

    this->state[MOUSE_LEFT]     = 0;
    this->state[MOUSE_RIGHT]    = 0;
    this->state[MOUSE_MIDDLE]   = 0;

    this->click = MouseClick;
    this->move  = MouseMove;

    return this;
}
