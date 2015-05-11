#include "includes.h"

/**
 * Création et initialisation d'un nouveau pointeur de type Array.
 * @return
 */
Array* libexp NewArray(void)
{
    Array *this = malloc(sizeof(Array));
    InitArray(this);

    return this;
}

/**
 * Initialisation des membres d'un structure Array.
 * @param this
 */
void libexp InitArray(Array *this)
{
    this->element = NULL;
    this->size = 0;

    this->add = ArrayAdd;
    this->remove = ArrayRemove;
    this->swap = ArraySwap;
    this->get = ArrayGet;

    this->clear = ArrayClear;
    this->free = FreeArray;
}

/**
 * Libération de la mémoire allouée pour une Array.
 * @param this
 */
void libexp FreeArray(Array *this)
{
    this->clear(this);
    free(this);
}

/**
 * Suppression de l'intégralité des éléments de la Array.
 * @param this
 */
void libexp ArrayClear(Array *this)
{
    size_t i;

    for(i = 0 ; i < this->size ; i++)
        free(this->element[i]);
    free(this->element);
    this->element = NULL;

    this->size = 0;
}

/**
 * Ajout d'un nouvel élément à une Array.
 * Si l'élément est déjà alloué, l'adresse en copiée. Sinon, un nouvel espace est
 * alloué et la valeur est copiée.
 * @param this
 * @param value
 * @param size
 * @param allocated
 * @return
 */
unsigned char libexp ArrayAdd(Array *this, void *value, size_t size, unsigned short allocated)
{
    if((this->element = realloc(this->element, ++this->size * sizeof(void*))) != NULL)
    {
        if(allocated)
            this->element[this->size-1] = value;
        else
        {
            if((this->element[this->size-1] = malloc(size)) == NULL)
            {
                this->element = realloc(this->element, --this->size * sizeof(void*));
                return 0;
            }
            else
                memcpy(this->element[this->size-1], value, size);
        }

        return 1;
    }

    return 0;
}

/**
 * Suppression de l'élément de Array situé à l'indice donné.
 * @param this
 * @param index
 * @return
 */
unsigned char libexp ArrayRemove(Array *this, size_t index)
{
    void **tmp = NULL;

    if(index >= 0 && index < this->size
    && (tmp = malloc(--this->size * sizeof(void*))) != NULL)
    {
        size_t i;
        unsigned char flag = 0;

        for(i = 0 ; i < this->size+1 ; i++)
        {
            if(i == index)
            {
                //On ne libère que l'élément qu'on souhaite supprimer
                free(this->element[i]);

                flag = 1;
                continue;
            }

            //Les autres éléments sont sauvegardés
            tmp[i - flag] = this->element[i];
        }
        free(this->element);

        this->element = tmp;
        return 1;
    }

    return 0;
}

/**
 * Inverse deux valeurs d'une Array situés aux indices donnés.
 * @param this
 * @param first
 * @param second
 * @return
 */
unsigned char libexp ArraySwap(Array *this, size_t first, size_t second)
{
    if(first >= 0 && first < this->size
    && second >= 0 && second < this->size)
    {
        void *tmp = this->element[first];
        this->element[first] = this->element[second];
        this->element[second] = tmp;

        return 1;
    }

    return 0;
}

/**
 * Renvoie le pointeur void correspondant à la valeur de l'élement à l'indice donné.
 * @param this
 * @param index
 * @return
 */
void* libexp ArrayGet(Array *this, size_t index)
{
    return (index >= 0 && index < this->size) ? this->element[index] : NULL;
}
