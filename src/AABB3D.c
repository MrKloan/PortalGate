#include "includes.h"

AABB3D *AABB3DRender(AABB3D *this)
{
    GLfloat red[] = {1.f, 0.f, 0.f, 1.f};

    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1.f, 0.f, 0.f);

        glMaterialfv(GL_FRONT, GL_AMBIENT, red);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		glMaterialfv(GL_FRONT, GL_SPECULAR, red);
		glMaterialfv(GL_FRONT, GL_SHININESS, red);
		glMaterialfv(GL_FRONT, GL_EMISSION, red);

        glTranslatef(this->x, this->y, this->z);

        glBegin(GL_QUADS);
            glVertex3f(this->w, this->h, 0.f);      // Top Right Of The Quad (Top)
            glVertex3f(0.f,     this->h, 0.f);      // Top Left Of The Quad (Top)
            glVertex3f(0.f,     this->h, this->d);  // Bottom Left Of The Quad (Top)
            glVertex3f(this->w, this->h, this->d);  // Bottom Right Of The Quad (Top)

            glVertex3f(this->w, 0.f,     this->d);  // Top Right Of The Quad (Bottom)
            glVertex3f(0.f,     0.f,     this->d);  // Top Left Of The Quad (Bottom)
            glVertex3f(0.f,     0.f,     0.f);      // Bottom Left Of The Quad (Bottom)
            glVertex3f(this->w, 0.f,     0.f);      // Bottom Right Of The Quad (Bottom)

            glVertex3f(this->w, this->h, this->d);  // Top Right Of The Quad (Front)
            glVertex3f(0.f,     this->h, this->d);  // Top Left Of The Quad (Front)
            glVertex3f(0.f,     0.f,     this->d);  // Bottom Left Of The Quad (Front)
            glVertex3f(this->w, 0.f,     this->d);  // Bottom Right Of The Quad (Front)

            glVertex3f(this->w, 0.f,     0.f);      // Top Right Of The Quad (Back)
            glVertex3f(0.f,     0.f,     0.f);      // Top Left Of The Quad (Back)
            glVertex3f(0.f,     this->h, 0.f);      // Bottom Left Of The Quad (Back)
            glVertex3f(this->w, this->h, 0.f);      // Bottom Right Of The Quad (Back)

            glVertex3f(0.f,     this->h, this->d);  // Top Right Of The Quad (Left)
            glVertex3f(0.f,     this->h, 0.f);      // Top Left Of The Quad (Left)
            glVertex3f(0.f,     0.f,     0.f);      // Bottom Left Of The Quad (Left)
            glVertex3f(0.f,     0.f,     this->d);  // Bottom Right Of The Quad (Left)

            glVertex3f(this->w, this->h, 0.f);      // Top Right Of The Quad (Right)
            glVertex3f(this->w, this->h, this->d);  // Top Left Of The Quad (Right)
            glVertex3f(this->w, 0.f,     this->d);  // Bottom Left Of The Quad (Right)
            glVertex3f(this->w, 0.f,     0.f);      // Bottom Right Of The Quad (Right)
        glEnd();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();

    return this;
}

unsigned char AABB3DCollide(AABB3D *this, AABB3D *box)
{
    if((box->x >= this->x + this->w) //Trop à droite
    || (box->x + box->w <= this->x)  //Trop à gauche
    || (box->y >= this->y + this->h) //Trop en bas
    || (box->y + box->h <= this->y)  //Trop en haut
    || (box->z >= this->z + this->d) //Trop derrière
    || (box->z + box->d <= this->z)) //Trop devant
          return 0;
   else
          return 1;
}

void AABB3DFree(AABB3D *this)
{
    free(this);
}

AABB3D *NewAABB3D(float x, float y, float z, float w, float h, float d, float ax, float ay, float az)
{
    AABB3D *this = NULL;

    if((this = malloc(sizeof(AABB3D))) != NULL)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->h = h;
        this->d = d;
        this->ax = ax;
        this->ay = ay;
        this->az = az;

        this->render = AABB3DRender;
        this->collide = AABB3DCollide;
        this->free = AABB3DFree;
    }

    return this;
}
