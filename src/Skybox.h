#ifndef SKYBOX_H
#define SKYBOX_H

#define SKY_DISTANCE 1.f

typedef struct Skybox {
    GLuint textures[1];

    struct Skybox *(*render)(struct Skybox*);
    void (*free)(struct Skybox*);
} Skybox;

Skybox* NewSkybox(void);

#endif // SKYBOX_H
