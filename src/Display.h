#ifndef DISPLAY
#define DISPLAY

#define DISPLAY_TICK 20 // 20 = 1000/20 = 50FPS

typedef struct Display {
    int *argc;
    char **argv;
    unsigned char running;
    unsigned char fullscreen;
    int width, height;

    Keyboard *keyboard;
    Mouse *mouse;

    void (*init)(struct Display*);
    void (*free)(struct Display*);
    void (*start)(void);

    void (*idle)(void);
    void (*tick)(int);
    void (*render)(void);
    void (*resize)(int, int);
    void (*keys)(unsigned char, int, int);
    void (*keysUp)(unsigned char, int, int);
    void (*specials)(int, int, int);
    void (*specialsUp)(int, int, int);
    void (*click)(int, int, int, int);
    void (*motion)(int, int);
    void (*pressed)(int, int);
    void (*entry)(int);
} Display;

Display *NewDisplay(int*, char**, unsigned char);
void color4_to_float4(const struct aiColor4D*, float[4]);
void set_float4(float[4], float, float, float, float);
void apply_material(const struct aiMaterial*);
void recursive_render(const struct aiScene*, const struct aiNode*);

#endif
