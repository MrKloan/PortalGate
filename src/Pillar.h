#ifndef PILLAR_H
#define PILLAR_H

typedef struct Pillar {
    float x, y, z, height;
    GLuint textures[2];
    AABB3D *box;

    struct Pillar *(*render)(struct Pillar*);
    void (*free)(struct Pillar*);
} Pillar;

Pillar *NewPillar(short, short, short);
void generatePillars(void);
unsigned char pillarsCollide(AABB3D*);

#endif // PILLAR_H
