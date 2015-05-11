#include "includes.h"

Tile *TileRender(Tile *this)
{
	GLfloat green[] = {0.0, 1.0, 0.0, 1.0};

    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glTranslatef(0.f, 0.01f, 0.f);

        glMaterialfv(GL_FRONT, GL_AMBIENT, green);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
		glMaterialfv(GL_FRONT, GL_SPECULAR, green);
		glMaterialfv(GL_FRONT, GL_SHININESS, green);
		glMaterialfv(GL_FRONT, GL_EMISSION, green);

        glBegin(GL_QUADS);
            glVertex3f(this->x, this->y, this->z);
            glVertex3f(this->x, this->y, this->z + this->size);
            glVertex3f(this->x + this->size, this->y, this->z + this->size);
            glVertex3f(this->x + this->size, this->y, this->z);
        glEnd();
    glPopMatrix();

    return this;
}

Tile *NewTile(float x, float y, float z, float size)
{
    Tile *this = malloc(sizeof(Tile));

    this->x     = x;
    this->y     = y;
    this->z     = z;
    this->size  = size;

    this->render = TileRender;

    return this;
}

void generateTiles(void)
{
    float f, g;

    for(f = -30.f ; f < 30.f ; f += 1.5f)
	{
        for(g = -30.f ; g < 30.f ; g += 1.5f)
        {
            Tile *t = NewTile(f, 0.f, g, 1.5f);
            tiles->add(tiles, t, sizeof(t), 1);
        }
	}
}
