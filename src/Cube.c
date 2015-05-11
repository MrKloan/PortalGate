#include "includes.h"

Cube *CubeLeft(Cube *this)
{
    AABB3D *tmp = NewAABB3D(this->box->x - 1.5f, this->box->y, this->box->z,
                            this->box->w, this->box->h, this->box->d,
                            this->box->ax, this->box->ay, this->box->az);

    if(this->x - 1.5f >= -30.f && !this->collides(tmp))
    {
        this->moving = 1;

        if(this->angleZ != 0.f)
            this->angleZ = 0.f;

        this->angleX += 10.f;
        this->box->az += 10.f;

        if(this->angleX >= 90.f)
        {
            this->x                 -= 1.5f;
            this->box->x            -= 1.5f;
            this->angleX            = 0.f;
            this->box->az           = 0.f;
            this->move[CUBE_LEFT]   = 0;
            this->moving            = 0;

            if(hasWon(this))
                sounds->play(sounds, "victory", 0, 1.f);
        }
    }
    else
    {
        this->move[CUBE_LEFT]  = 0;
        this->moving            = 0;
    }

    tmp->free(tmp);
    return this;
}

Cube *CubeRight(Cube *this)
{
    AABB3D *tmp = NewAABB3D(this->box->x + 1.5f, this->box->y, this->box->z,
                            this->box->w, this->box->h, this->box->d,
                            this->box->ax, this->box->ay, this->box->az);

    if(this->x + 1.5f <= 30.f && !this->collides(tmp))
    {
        if(this->angleZ != 0.f)
            this->angleZ = 0.f;

        this->angleX -= 10.f;
        this->box->az -= 10.f;

        if(this->angleX <= -90.f)
        {
            this->x                 += 1.5f;
            this->box->x            += 1.5f;
            this->angleX            = 0.f;
            this->box->az           = 0.f;
            this->move[CUBE_RIGHT]  = 0;
            this->moving            = 0;

            if(hasWon(this))
                sounds->play(sounds, "victory", 0, 1.f);
        }
    }
    else
    {
        this->move[CUBE_RIGHT]  = 0;
        this->moving            = 0;
    }

    tmp->free(tmp);
    return this;
}

Cube *CubeForward(Cube *this)
{
    AABB3D *tmp = NewAABB3D(this->box->x, this->box->y, this->box->z - 1.5f,
                            this->box->w, this->box->h, this->box->d,
                            this->box->ax, this->box->ay, this->box->az);

    if(this->z - 1.5f >= -30.f && !this->collides(tmp))
    {
        if(this->angleX != 0.f)
            this->angleX = 0.f;

        this->angleZ -= 10.f;
        this->box->ax -= 10.f;

        if(this->angleZ <= -90.f)
        {
            this->z                     -= 1.5f;
            this->box->z                -= 1.5f;
            this->angleZ                = 0.f;
            this->box->ax               = 0.f;
            this->move[CUBE_FORWARD]    = 0;
            this->moving                = 0;

            if(hasWon(this))
                sounds->play(sounds, "victory", 0, 1.f);
        }
    }
    else
    {
        this->move[CUBE_FORWARD]    = 0;
        this->moving                = 0;
    }

    tmp->free(tmp);
    return this;
}

Cube *CubeBack(Cube *this)
{
    AABB3D *tmp = NewAABB3D(this->box->x, this->box->y, this->box->z + 1.5f,
                            this->box->w, this->box->h, this->box->d,
                            this->box->ax, this->box->ay, this->box->az);

    if(this->z + 1.5f <= 30.f && !this->collides(tmp))
    {
        if(this->angleX != 0.f)
            this->angleX = 0.f;

        this->angleZ += 10.f;
        this->box->ax += 10.f;

        if(this->angleZ >= 90.f)
        {
            this->z                 += 1.5f;
            this->box->z            += 1.5f;
            this->angleZ            = 0.f;
            this->box->ax           = 0.f;
            this->move[CUBE_BACK]   = 0;
            this->moving            = 0;

            if(hasWon(this))
                sounds->play(sounds, "victory", 0, 1.f);
        }
    }
    else
    {
        this->move[CUBE_BACK]   = 0;
        this->moving            = 0;
    }

    tmp->free(tmp);
    return this;
}

unsigned char CubeCollides(AABB3D *tmp)
{
    return (pillarsCollide(tmp)
         || stargate->collides(stargate, tmp)
         || turretsCollide(tmp));
}

Cube *CubeRender(Cube *this)
{
    //this->box->render(this->box);

    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);

        //Forward
        if(this->angleZ < 0)
        {
            glTranslatef(0.70f, -0.56f, -0.52f);
                glRotatef(this->angleZ, 1.f, 0.f, 0.f);
            glTranslatef(-0.70, 0.56f, 0.52f);
        }
        //Back
        else if(this->angleZ > 0)
        {
            glTranslatef(0.5f, -0.56f, 0.98f);
                glRotatef(this->angleZ, 1.f, 0.f, 0.f);
            glTranslatef(-0.5f, 0.56f, -0.98f);
        }
        //Left
        else if(this->angleX > 0)
        {
            glTranslatef(-0.8f, -0.56f, 0.75f);
                glRotatef(this->angleX, 0.f, 0.f, 1.f);
            glTranslatef(0.8f, 0.56f, -0.75f);
        }
        //Right
        else if(this->angleX < 0)
        {
            glTranslatef(0.68f, -0.56f, 0.52f);
                glRotatef(this->angleX, 0.f, 0.f, 1.f);
            glTranslatef(-0.68f, 0.56f, -0.52f);
        }

        glPushMatrix();
            glScalef(0.3, 0.3, 0.3);
            recursive_render(this->scene, this->scene->mRootNode);
        glPopMatrix();
    glPopMatrix();

    return this;
}

void CubeFree(Cube *this)
{
    aiReleaseImport(this->scene);
    this->box->free(this->box);
    free(this);
}

Cube *NewCube(void)
{
    Cube *this = malloc(sizeof(Cube));

    this->angleX = 0.f;
    this->angleZ = 0.f;

    this->x = 0.81f;
    this->y = 0.54f;
    this->z = 29.02f;

    this->moving = 0;
    this->move[CUBE_FORWARD] = 0;
    this->move[CUBE_BACK] = 0;
    this->move[CUBE_LEFT] = 0;
    this->move[CUBE_RIGHT] = 0;

    this->scene     = aiImportFile("data/models/companion.blend", aiProcessPreset_TargetRealtime_MaxQuality);
    this->box       = NewAABB3D(0.f, 0.f, 28.5f,
                                1.5f, 1.5f, 1.5f,
                                0.f, 0.f, 0.f);

    this->left      = CubeLeft;
    this->right     = CubeRight;
    this->forward   = CubeForward;
    this->back      = CubeBack;

    this->collides  = CubeCollides;
    this->render    = CubeRender;
    this->free      = CubeFree;

    return this;
}

unsigned char hasWon(Cube *this)
{
    //printf("x: %.20f, z: %.20f\n", this->x, this->z);
    return (this->x >= 0.809f && this->x < 0.82f && this->z == -23.480000f);
}
