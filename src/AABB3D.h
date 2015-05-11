#ifndef AABB3D_H
#define AABB3D_H

typedef struct AABB3D {
    float x, y, z;
    float w, h, d;
    float ax, ay, az;

    struct AABB3D *(*render)(struct AABB3D*);
    unsigned char (*collide)(struct AABB3D*, struct AABB3D*);
    void (*free)(struct AABB3D*);
} AABB3D;

AABB3D *NewAABB3D(float, float, float, float, float, float, float, float, float);

#endif // AABB3D_H
