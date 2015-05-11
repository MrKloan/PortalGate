#include "includes.h"

void SoundLoad(SoundManager *this)
{
    //Tir de laser
    this->add(this, "laser/0");
    this->add(this, "laser/1");
    this->add(this, "laser/2");
    this->add(this, "laser/3");
    this->add(this, "laser/4");
    this->add(this, "laser/5");
    this->add(this, "laser/6");

    //Cible repérée
    this->add(this, "turret/turret_active_1");
    this->add(this, "turret/turret_active_2");
    this->add(this, "turret/turret_active_3");
    this->add(this, "turret/turret_active_4");
    this->add(this, "turret/turret_active_5");
    this->add(this, "turret/turret_active_6");
    this->add(this, "turret/turret_active_7");
    this->add(this, "turret/turret_active_8");

    //Cible perdue
    this->add(this, "turret/turret_retire_1");
    this->add(this, "turret/turret_retire_2");
    this->add(this, "turret/turret_retire_3");
    this->add(this, "turret/turret_retire_4");
    this->add(this, "turret/turret_retire_5");
    this->add(this, "turret/turret_retire_6");
    this->add(this, "turret/turret_retire_7");

    //Victoire
    this->add(this, "victory");
}

unsigned char SoundAdd(SoundManager *this, char *name)
{
    char path[100];

    strcpy(path, this->path);
    strcat(path, name);
    strcat(path, ".wav");

    if(file_exists(path))
    {
        Sound *sound = malloc(sizeof(Sound));

        sound->name = name;
        sound->buffer = alutCreateBufferFromFile(path);
        alGenSources(1, &sound->source);
        alSourcei(sound->source, AL_BUFFER, sound->buffer);

        this->sounds->add(this->sounds, sound, sizeof(sound), 1);

        printf("Sound loaded : %s\n", path);
        return 1;
    }
    else
    {
        printf("Sound file not found : %s\n", path);
        return 0;
    }
}

unsigned char SoundPlay(SoundManager *this, char *name, unsigned char loop, float volume)
{
    unsigned short i;

    for(i = 0 ; i < this->sounds->size ; i++)
    {
        Sound *sound = this->sounds->get(this->sounds, i);

        if(strcmp(sound->name, name) == 0)
        {
            alGetSourcei(sound->source, AL_SOURCE_STATE, &(sound->state));
            alSourcei(sound->source, AL_LOOPING, loop);
            alSourcef(sound->source, AL_GAIN, volume);
            alSourcePlay(sound->source);
            sound->playing = 1;

            return 1;
        }
    }

    printf("Sound resource not found : %s\n", name);
    return 0;
}

unsigned char SoundStop(SoundManager *this, char *name)
{
    unsigned short i;

    for(i = 0 ; i < this->sounds->size ; i++)
    {
        Sound *sound = this->sounds->get(this->sounds, i);

        if(strcmp(sound->name, name) == 0)
        {
            alSourceStop(sound->source);
            sound->playing = 0;
            return 1;
        }
    }

    printf("Sound resource not found : %s\n", name);
    return 0;
}

void SoundStopAll(SoundManager *this)
{
    unsigned short i;

    for(i = 0 ; i < this->sounds->size ; i++)
    {
        Sound *sound = this->sounds->get(this->sounds, i);

        if(sound->playing)
        {
            alSourceStop(sound->source);
            sound->playing = 0;
        }
    }
}

void SoundFree(SoundManager *this)
{
    unsigned short i;

    for(i = 0 ; i < this->sounds->size ; i++)
    {
        Sound *s = (Sound*)this->sounds->get(this->sounds, i);

        this->stop(this, s->name);
        alDeleteSources(1, &(s->source));
        alDeleteBuffers(1, &(s->buffer));
    }

    this->sounds->free(this->sounds);

    alutExit();
    free(this);
}

SoundManager *NewSoundManager(int *argc, char **argv, char *path)
{
    SoundManager *this = NULL;

    if((this = malloc(sizeof(SoundManager))) != NULL)
    {
        alutInit(argc, argv);
        alGetError(); //Clear OpenAl's error buffer

        this->path = path;
        this->sounds = NewArray();

        this->load = SoundLoad;
        this->add = SoundAdd;
        this->play = SoundPlay;
        this->stop = SoundStop;
        this->stopAll = SoundStopAll;
        this->free = SoundFree;
    }

    return this;
}
