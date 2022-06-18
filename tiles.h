#include <raylib.h>

#ifndef TILES_H
#define TILES_H

typedef struct{
	Color color;
	Vector3 position;
	Vector2 size;
	BoundingBox boundbox;
} Tile;

typedef struct{
	Vector2 tileSize;
	Vector2 mapDim;		// { width, height }
	Vector3 startPos;
	Tile** tilesGrid;	//of dimensions [width][height]

} TileMap;

TileMap createTileMap(Vector2, Vector2);
Tile createTile(Color, int, int, Vector2);
BoundingBox setBoundBox(Tile*);
//void drawTiles(Tile**, int);
void drawTiles(TileMap*);
void updateTilePosition(Tile*, Vector3);
RayCollision checkTileCollisions(Tile** ,int , Ray);

#endif
