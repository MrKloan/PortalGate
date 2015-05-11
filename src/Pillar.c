#include "includes.h"

Pillar *PillarRender(Pillar *this)
{
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glColor4f(1.f, 1.f, 1.f, 1.f);

        glMaterialfv(GL_FRONT, GL_AMBIENT, white);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT, GL_SHININESS, white);
        glMaterialfv(GL_FRONT, GL_EMISSION, white);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        //Face basse
        glBegin(GL_POLYGON);
            glTexCoord2d(0.33, 0.0);
            glVertex3f(0.5f, 0.0f, 0.0f);
            glTexCoord2d(0.66, 0.0);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glTexCoord2d(1.0, 0.33);
            glVertex3f(1.5f, 0.0f, 0.5f);
            glTexCoord2d(1.0, 0.66);
            glVertex3f(1.5f, 0.0f, 1.0f);
            glTexCoord2d(0.66, 1.0);
            glVertex3f(1.0f, 0.0f, 1.5f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, 0.0f, 1.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glTexCoord2d(0.0, 0.33);
            glVertex3f(0.0f, 0.0f, 0.5f);
        glEnd();

        //Face haute
        glBegin(GL_POLYGON);
            glTexCoord2d(0.0, 0.33);
            glVertex3f(0.0f, this->height, 0.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.0f, this->height, 1.0f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, this->height, 1.5f);
            glTexCoord2d(0.66, 1.0);
            glVertex3f(1.0f, this->height, 1.5f);
            glTexCoord2d(1.0, 0.66);
            glVertex3f(1.5f, this->height, 1.0f);
            glTexCoord2d(1.0, 0.33);
            glVertex3f(1.5f, this->height, 0.5f);
            glTexCoord2d(0.66, 0.0);
            glVertex3f(1.0f, this->height, 0.0f);
            glTexCoord2d(0.33, 0.0);
            glVertex3f(0.5f, this->height, 0.0f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, this->textures[1]);
        //Face arrière
        glBegin(GL_QUADS);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, this->height, 0.0f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(1.0f, this->height, 0.0f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, 0.0f, 0.0f);
        glEnd();

        //Face arrière-droite
        glBegin(GL_QUADS);
            glTexCoord2d(0.66, 0.0);
            glVertex3f(1.0f, this->height, 0.0f);
            glTexCoord2d(1.0, 0.33);
            glVertex3f(1.5f, this->height, 0.5f);
            glTexCoord2d(1.0, 0.33);
            glVertex3f(1.5f, 0.0f, 0.5f);
            glTexCoord2d(0.66, 0.0);
            glVertex3f(1.0f, 0.0f, 0.0f);
        glEnd();

        //Face droite
        glBegin(GL_QUADS);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(1.5f, this->height, 0.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(1.5f, this->height, 1.0f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(1.5f, 0.0f, 1.0f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(1.5f, 0.0f, 0.5f);
        glEnd();

        //Face avant-droite
        glBegin(GL_QUADS);
            glTexCoord2d(1.0, 0.66);
            glVertex3f(1.5f, this->height, 1.0f);
            glTexCoord2d(0.66, 1.0);
            glVertex3f(1.0f, this->height, 1.5f);
            glTexCoord2d(0.66, 1.0);
            glVertex3f(1.0f, 0.0f, 1.5f);
            glTexCoord2d(1.0, 0.66);
            glVertex3f(1.5f, 0.0f, 1.0f);
        glEnd();

        //Face avant
        glBegin(GL_QUADS);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(1.0f, this->height, 1.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.5f, this->height, 1.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.5f, 0.0f, 1.5f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(1.0f, 0.0f, 1.5f);
        glEnd();

        //Face avant-gauche
        glBegin(GL_QUADS);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, this->height, 1.5f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.0f, this->height, 1.0f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.5f, 0.0f, 1.5f);
        glEnd();

        //Face gauche
        glBegin(GL_QUADS);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.0f, this->height, 1.0f);
            glTexCoord2d(0.0, 0.66);
            glVertex3f(0.0f, this->height, 0.5f);
            glTexCoord2d(0.0, 0.33);
            glVertex3f(0.0f, 0.0f, 0.5f);
            glTexCoord2d(0.33, 1.0);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();

        //Face arrière-gauche
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.33);
            glVertex3f(0.0f, this->height, 0.5f);
            glTexCoord2d(0.33, 0.0);
            glVertex3f(0.5f, this->height, 0.0f);
            glTexCoord2d(0.33, 0.0);
            glVertex3f(0.5f, 0.0f, 0.0f);
            glTexCoord2d(0.0, 0.33);
            glVertex3f(0.0f, 0.0f, 0.5f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //this->box->render(this->box);

    return this;
}

void PillarFree(Pillar *this)
{
    free(this);
}

Pillar *NewPillar(short x, short z, short height)
{
    Pillar *this = malloc(sizeof(Pillar));
    float tileSize = 1.5f;

    this->x = tileSize*x;
    this->y = 0.f;
    this->z = tileSize*z;
    this->height = (float)height;

    this->textures[0] = SOIL_load_OGL_texture("data/textures/pillar.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA);
    this->textures[1] = SOIL_load_OGL_texture("data/textures/pillar.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA);

    this->box = NewAABB3D(this->x,  this->y,        this->z,
                          1.5f,     this->height,   1.5f,
                          0.f,      0.f,            0.f);

    this->render = PillarRender;
    this->free = PillarFree;

    return this;
}

void generatePillars(void)
{
    short i, x, z, height;

    for(i = 0 ; i < 15 ; i++)
    {
        x = (rand() % 31) - 15;
        z = (rand() % 31) - 15;
        height = rand()%30;

        Pillar *p = NewPillar(x, z, height);
        pillars->add(pillars, p, sizeof(p), 1);
    }
}

unsigned char pillarsCollide(AABB3D *box)
{
    size_t i;

    for(i = 0 ; i < pillars->size ; i++)
    {
        Pillar *p = (Pillar*)pillars->get(pillars, i);

        if(p != NULL && box->collide(box, p->box))
            return 1;
    }

    return 0;
}
