#ifndef CAMERA
#define CAMERA

typedef struct Camera {
    float angle, deltaAngle, speed, rotateSpeed;
    float x, y, z;
    float lx, ly, lz;
    unsigned char invertX, invertY;

    struct Camera *(*right)(struct Camera*);
    struct Camera *(*left)(struct Camera*);
    struct Camera *(*forward)(struct Camera*);
    struct Camera *(*back)(struct Camera*);
    struct Camera *(*up)(struct Camera*);
    struct Camera *(*down)(struct Camera*);
    struct Camera *(*lookRight)(struct Camera*);
    struct Camera *(*lookLeft)(struct Camera*);
    struct Camera *(*lookUp)(struct Camera*);
    struct Camera *(*lookDown)(struct Camera*);
} Camera;

Camera *NewCamera(unsigned char, unsigned char);

#endif
