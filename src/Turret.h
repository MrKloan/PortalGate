#ifndef TURRET_H
#define TURRET_H

typedef struct Turret {
    float x, y, z;
    AABB3D *box, *fireBox;
    const struct aiScene *scene;
    unsigned char target, monitoring;

    struct Turret *(*render)(struct Turret*);
    struct Turret *(*ai)(struct Turret*);
    unsigned char(*check)(struct Turret*, unsigned short);
    void (*fire)(struct Turret*);
    void (*free)(struct Turret*);
} Turret;

Turret *NewTurret(short, short);
void generateTurrets(void);
unsigned char turretsCollide(AABB3D*);

#endif // TURRET_H
