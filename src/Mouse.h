#ifndef MOUSE
#define MOUSE

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2

typedef struct Mouse {
    int x, y;
    int px, py;
    unsigned char inWindow;

    unsigned char state[3];
    struct Mouse *(*click)(struct Mouse*);
    struct Mouse *(*move)(struct Mouse*);
} Mouse;

Mouse *NewMouse(void);

#endif // MOUSE
