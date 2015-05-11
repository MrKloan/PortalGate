#ifndef STARGATE_H
#define STARGATE_H

typedef struct Stargate {
    float x, y, z;
    const struct aiScene *scene;
    AABB3D *box[2];

    struct Stargate *(*render)(struct Stargate*);
    unsigned char (*collides)(struct Stargate*, AABB3D*);
    void (*free)(struct Stargate*);
} Stargate;

Stargate *NewStargate(void);

#endif // STARGATE_H
