#include "includes.h"

Camera *CameraLeft(Camera *this)
{
    float s = sin(this->angle + PI/2.f);
    float c = -cos(this->angle + PI/2.f);

    if(this->x - s * this->speed > -29.f
    && this->z - c * this->speed > -29.f
    && this->x - s * this->speed < 29.f
    && this->z - c * this->speed < 29.f)
    {
        this->x -= s * this->speed;
        this->z -= c * this->speed;
    }

    return this;
}

Camera *CameraRight(Camera *this)
{
    float s = sin(this->angle + PI/2.f);
    float c = -cos(this->angle + PI/2.f);

    if(this->x + s * this->speed > -29.f
    && this->z + c * this->speed > -29.f
    && this->x + s * this->speed < 29.f
    && this->z + c * this->speed < 29.f)
    {
        this->x += s * this->speed;
        this->z += c * this->speed;
    }

    return this;
}

Camera *CameraForward(Camera *this)
{
    if(this->x + this->lx * this->speed > -29.f
    && this->z + this->lz * this->speed > -29.f
    && this->x + this->lx * this->speed < 29.f
    && this->z + this->lz * this->speed < 29.f)
    {
        this->x += this->lx * this->speed;
        this->z += this->lz * this->speed;
    }

    return this;
}

Camera *CameraBack(Camera *this)
{
    if(this->x - this->lx * this->speed > -29.f
    && this->z - this->lz * this->speed > -29.f
    && this->x - this->lx * this->speed < 29.f
    && this->z - this->lz * this->speed < 29.f)
    {
        this->x -= this->lx * this->speed;
        this->z -= this->lz * this->speed;
    }

    return this;
}

Camera *CameraUp(Camera *this)
{
    if(this->y + this->ly * this->speed < 29.f)
        this->y += /*this->ly **/ this->speed;

    return this;
}

Camera *CameraDown(Camera *this)
{
    if(this->y - this->ly * this->speed >= 1.f)
        this->y -= /*this->ly **/ this->speed;

    return this;
}

Camera *CameraLookLeft(Camera *this)
{
    this->angle -= this->speed/this->rotateSpeed;
    this->lx    = sin(this->angle);
    this->lz    = -cos(this->angle);

    return this;
}

Camera *CameraLookRight(Camera *this)
{
    this->angle += this->speed/this->rotateSpeed;
    this->lx    = sin(this->angle);
    this->lz    = -cos(this->angle);

    return this;
}

Camera *CameraLookUp(Camera *this)
{
    if(this->ly <= 90.f)
        this->ly += this->speed / (this->rotateSpeed*1.5f);

    return this;
}

Camera *CameraLookDown(Camera *this)
{
    if(this->ly >= -90.f)
        this->ly -= this->speed / (this->rotateSpeed*1.5f);

    return this;
}

Camera *NewCamera(unsigned char invertX, unsigned char invertY)
{
    Camera *this        = malloc(sizeof(Camera));

    this->angle         = 0.f;
    this->deltaAngle    = 0.f;
    this->x             = 0.f;
    this->y             = 20.f;
    this->z             = 28.f;
    this->lx            = 0.f;
    this->ly            = -0.5f;
    this->lz            = -1.f;
    this->speed         = 0.3f;
    this->rotateSpeed   = 10.f;
    this->invertX       = invertX;
    this->invertY       = invertY;

    this->left          = CameraLeft;
    this->right         = CameraRight;
    this->forward       = CameraForward;
    this->back          = CameraBack;
    this->up            = CameraUp;
    this->down          = CameraDown;
    this->lookLeft      = CameraLookLeft;
    this->lookRight     = CameraLookRight;
    this->lookUp        = CameraLookUp;
    this->lookDown      = CameraLookDown;

    return this;
}
