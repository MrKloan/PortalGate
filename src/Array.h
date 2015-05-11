#ifndef ARRAY_H
#define ARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef WIN32
    #define libimp __declspec(dllimport)
    #define libexp __declspec(dllexport)
#elif defined (linux)
    #define libimp
    #define libexp
#else
    #error "Nope."
#endif

typedef struct Array {
    void **element;
    size_t size;

    unsigned char (*add)(struct Array*, void*, size_t, unsigned short);
    unsigned char (*remove)(struct Array*, size_t);
    unsigned char (*swap)(struct Array*, size_t, size_t);
    void *(*get)(struct Array*, size_t);

    void (*clear)(struct Array*);
    void (*free)(struct Array*);
} Array;

Array* libimp NewArray(void);
void libimp InitArray(Array*);
void libimp FreeArray(Array*);
void libimp ArrayClear(Array*);

unsigned char libimp ArrayAdd(Array*, void*, size_t, unsigned short);
unsigned char libimp ArrayRemove(Array*, size_t);
unsigned char libimp ArraySwap(Array*, size_t, size_t);
void* libimp ArrayGet(Array*, size_t);

#ifdef	__cplusplus
}
#endif

#endif // ARRAY_H
