#include "includes.h"

Turret *TurretRender(Turret *this)
{
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glPushMatrix();
            recursive_render(this->scene, this->scene->mRootNode);
        glPopMatrix();
    glPopMatrix();

    //this->box->render(this->box);

    return this;
}

Turret *TurretAI(Turret *this)
{
    if(this->fireBox != NULL || this->check(this, 5))
    {
        //Acquisition de la cible
        if(this->monitoring == 1)
        {
            char path[23];
            sprintf(path, "turret/turret_active_%d", rand()%8 + 1);

            sounds->play(sounds, path, 0, 1.f);
            this->monitoring = 0;
        }

        //Tir de laser
        if(this->target == 1 && this->fireBox == NULL)
        {
            char path[8];
            sprintf(path, "laser/%d", rand()%7);

            sounds->play(sounds, path, 0, 0.15f);
        }
        this->fire(this);
    }
    else if(this->monitoring == 0)
    {
        char path[23];
        sprintf(path, "turret/turret_retire_%d", rand()%7 + 1);

        sounds->play(sounds, path, 0, 1.f);
        this->monitoring = 1;
    }

    return this;
}

void TurretFree(Turret *this)
{
    aiReleaseImport(this->scene);
    this->box->free(this->box);
    free(this);
}

unsigned char TurretCheck(Turret *this, unsigned short range)
{
    AABB3D *box = NewAABB3D(this->x - range*1.5f, this->y, this->z - range*1.5f,
                            range*1.5f*2.f, 1.5f, range*1.5f*2.f,
                            0.f, 0.f, 0.f);
    this->target = box->collide(box, cube->box);

    box->free(box);
    return this->target;
}

void TurretFire(Turret *this)
{
    if(this->fireBox == NULL)
        this->fireBox = NewAABB3D(this->x + 0.14f, this->y + 1.016f, this->z - 0.46f,
                                  0.016f, 0.016f, 1.4f,
                                  0.f, 0.f, 0.f);

    this->fireBox->z++;

    if(this->fireBox->z >= 30.f)
    {
        this->fireBox->free(this->fireBox);
        this->fireBox = NULL;
    }
    else
    {
        GLfloat red[]           = {1.0, 0.0, 0.0, 1.0};
        GLUquadricObj *quad     = gluNewQuadric();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, red);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
            glMaterialfv(GL_FRONT, GL_SPECULAR, red);
            glMaterialfv(GL_FRONT, GL_SHININESS, red);
            glMaterialfv(GL_FRONT, GL_EMISSION, red);

            glTranslatef(this->fireBox->x, this->fireBox->y, this->fireBox->z);
            gluCylinder(quad, this->fireBox->w, this->fireBox->h, this->fireBox->d, 50, 50);

            glTranslatef(-0.46f, 0.f, 0.f);
            gluCylinder(quad, this->fireBox->w, this->fireBox->h, this->fireBox->d, 50, 50);
        glPopMatrix();

        //Si le cube est touché par un tir, on le replace à sa position de départ
        if(this->fireBox->collide(this->fireBox, cube->box))
        {
            cube->x = 0.81f;
            cube->y = 0.54f;
            cube->z = 29.02f;

            cube->box->x = 0.f;
            cube->box->y = 0.f;
            cube->box->z = 28.5f;
        }
        //Si le tir touche un pilier, dsparition du tir
        else if(pillarsCollide(this->fireBox))
        {
            this->fireBox->free(this->fireBox);
            this->fireBox = NULL;
        }
    }
}

Turret *NewTurret(short x, short z)
{
    Turret *this = malloc(sizeof(Turret));
    float tileSize = 1.5f;

    this->x = -0.65f + tileSize*x;
    this->y = -0.1f;
    this->z = -0.3f + tileSize*z;

    this->box = NewAABB3D(this->x - 0.5f, this->y, this->z - 0.9f,
                          1.f, 1.5f, 1.f,
                          0.f, 0.f, 0.f);

    this->target = 0;
    this->monitoring = 1;

    this->fireBox   = NULL;

    this->scene     = aiImportFile("data/models/turret.3ds", aiProcessPreset_TargetRealtime_MaxQuality);

    this->render    = TurretRender;
    this->ai        = TurretAI;
    this->check     = TurretCheck;
    this->fire      = TurretFire;
    this->free      = TurretFree;

    return this;
}

void generateTurrets(void)
{
    short i, nb, x, z;

    nb = rand() % 10 + 1;

    for(i = 0 ; i < nb ; i++)
    {
        x = (rand() % 31) - 15;
        z = (rand() % 31) - 15;

        Turret *t = NewTurret(x, z);
        turrets->add(turrets, t, sizeof(t), 1);
    }
}

unsigned char turretsCollide(AABB3D *box)
{
    size_t i;

    for(i = 0 ; i < turrets->size ; i++)
    {
        Turret *t = (Turret*)turrets->get(turrets, i);

        if(t != NULL && box->collide(box, t->box))
            return 1;
    }

    return 0;
}
