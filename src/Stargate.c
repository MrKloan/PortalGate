#include "includes.h"

Stargate *StargateRender(Stargate *this)
{
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glPushMatrix();
            glScalef(0.3, 0.3, 0.3);
            recursive_render(this->scene, this->scene->mRootNode);
        glPopMatrix();
    glPopMatrix();

    /*/
    this->box[0]->render(this->box[0]);
    this->box[1]->render(this->box[1]);//*/

    return this;
}

unsigned char StargateCollides(Stargate *this, AABB3D *box)
{
    return (this->box[0]->collide(this->box[0], box)
         || this->box[1]->collide(this->box[1], box));
}

void StargateFree(Stargate *this)
{
    aiReleaseImport(this->scene);
    this->box[0]->free(this->box[0]);
    this->box[1]->free(this->box[1]);
    free(this);
}

Stargate *NewStargate(void)
{
    Stargate *this = malloc(sizeof(Stargate));

    this->x = 0.81f;
    this->y = 0.f;
    this->z = -18.5f;

    this->box[0]    = NewAABB3D(this->x - 0.8f, this->y, this->z - 2.5f,
                                1.4f, 1.5f, 1.5f,
                                0.f, 0.f, 0.f);
    this->box[1]    = NewAABB3D(this->x - 6.f, this->y, this->z - 11.5f,
                                12.f, 6.f, 5.f,
                                0.f, 0.f, 0.f);

    this->scene     = aiImportFile("data/models/Stargate.obj", aiProcessPreset_TargetRealtime_MaxQuality);

    this->render    = StargateRender;
    this->collides  = StargateCollides;
    this->free      = StargateFree;

    return this;
}
