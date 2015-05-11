#ifndef SOUND_H
#define SOUND_H

typedef struct Sound {
    char *name;
    ALuint source, buffer;
    ALint state;
    unsigned char playing;
} Sound;

typedef struct SoundManager {
    char *path;
    Array *sounds;

    void (*load)(struct SoundManager*);
    unsigned char (*add)(struct SoundManager*, char*);
    unsigned char (*play)(struct SoundManager*, char*, unsigned char, float);
    unsigned char (*stop)(struct SoundManager*, char*);
    void (*stopAll)(struct SoundManager*);
    void (*free)(struct SoundManager*);
} SoundManager;

SoundManager *NewSoundManager(int*, char**, char*);

#endif // SOUND_H
