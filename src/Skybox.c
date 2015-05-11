#include "includes.h"

Skybox* SkyboxRender(Skybox *this)
{
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);

        glTranslatef(0.f, 0.f, 0.f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        //Face
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex3f(-30.f, 30.f, 30.f);
            glTexCoord2f(1, 1);
            glVertex3f(30.f, 30.f, 30.f);
            glTexCoord2f(1, 0);
            glVertex3f(30.f, 0.f, 30.f);
            glTexCoord2f(0, 0);
            glVertex3f(-30.f, 0.f, 30.f);
        glEnd();

        //Left
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex3f(-30.f, 30.f, -30.f);
            glTexCoord2f(1, 1);
            glVertex3f(-30.f, 30.f, 30.f);
            glTexCoord2f(1, 0);
            glVertex3f(-30.f, 0.f, 30.f);
            glTexCoord2f(0, 0);
            glVertex3f(-30.f, 0.f, -30.f);
        glEnd();

        //Back
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-30.f, 0.f, -30.f);
            glTexCoord2f(1, 0);
            glVertex3f(30.f, 0.f, -30.f);
            glTexCoord2f(1, 1);
            glVertex3f(30.f, 30.f, -30.f);
            glTexCoord2f(0, 1);
            glVertex3f(-30.f, 30.f, -30.f);
        glEnd();

        //Right
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(30.f, 0.f, -30.f);
            glTexCoord2f(1, 0);
            glVertex3f(30.f, 0.f, 30.f);
            glTexCoord2f(1, 1);
            glVertex3f(30.f, 30.f, 30.f);
            glTexCoord2f(0, 1);
            glVertex3f(30.f, 30.f, -30.f);
        glEnd();

        //Top
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(1, 1);
            glVertex3f(30.f, 30.f, -30.f);
            glTexCoord2f(1, 0);
            glVertex3f(30.f, 30.f, 30.f);
            glTexCoord2f(0, 0);
            glVertex3f(-30.f, 30.f, 30.f);
            glTexCoord2f(0, 1);
            glVertex3f(-30.f, 30.f, -30.f);
        glEnd();

        /*/Bottom
        glBindTexture(GL_TEXTURE_2D, this->textures[5]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex3f(-30.f, 0.f, -30.f);
            glTexCoord2f(0, 0);
            glVertex3f(-30.f, 0.f, 30.f);
            glTexCoord2f(1, 0);
            glVertex3f(30.f, 0.f, 30.f);
            glTexCoord2f(1, 1);
            glVertex3f(30.f, 0.f, -30.f);
        glEnd();*/

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    return this;
}

void SkyboxFree(Skybox *this)
{
    free(this);
}

Skybox *NewSkybox(void)
{
    Skybox *this = malloc(sizeof(Skybox));

    this->textures[0] = SOIL_load_OGL_texture("data/textures/skybox.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA);

    this->render = SkyboxRender;
    this->free = SkyboxFree;

    return this;
}
