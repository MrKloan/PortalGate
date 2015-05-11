#ifndef CUBE_H
#define CUBE_H

enum {
    CUBE_FORWARD,
    CUBE_BACK,
    CUBE_LEFT,
    CUBE_RIGHT
};

typedef struct Cube {
    float angleX, angleZ;
    float x, y, z;
    const struct aiScene *scene;
    AABB3D *box;

    unsigned char moving;
    unsigned char move[4];

    struct Cube *(*left)(struct Cube*);
    struct Cube *(*right)(struct Cube*);
    struct Cube *(*forward)(struct Cube*);
    struct Cube *(*back)(struct Cube*);

    unsigned char (*collides)(AABB3D*);
    struct Cube *(*render)(struct Cube*);
    void (*free)(struct Cube*);
} Cube;

Cube *NewCube(void);
unsigned char hasWon(Cube*);

#endif // CUBE_H
