#ifndef KEYBOARD
#define KEYBOARD

#define KEY_UP 256
#define KEY_DOWN 257
#define KEY_LEFT 258
#define KEY_RIGHT 259

typedef struct Keyboard {
    unsigned char keys[260];

    struct Keyboard *(*handle)(struct Keyboard*);
} Keyboard;

Keyboard *NewKeyboard(void);

#endif // KEYBOARD
