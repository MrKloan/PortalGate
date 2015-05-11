#ifndef TILE_H
#define TILE_H

typedef struct Tile {
    float x, y, z, size;

    struct Tile *(*render)(struct Tile*);
} Tile;

Tile *NewTile(float, float, float, float);
void generateTiles(void);

#endif
