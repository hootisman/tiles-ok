#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

extern bool DEBUG_MODE;

TileMap createTileMap(Vector2 size, Vector2 dim){
	// Returns reference of a TileMap
	
	TileMap map = {
		.tileSize = size,			// { x, y }
		.mapDim = dim,			// { width, height }
		.startPos = { 1.0f, 0.0f, 1.0f },	//default start position
	};

	// Making tiles grid
	
	Color color = { 0, 0, 0, 255};	//default color
	float width = dim.x;
	float height = dim.y;


	Tile** grid = (Tile**)malloc(sizeof(Tile*) * height);		//height of grid	
	

	for(int i = 0; i < height; i++){
		//allocates each row of grid 
		grid[i] = (Tile*)malloc(sizeof(Tile) * width);		//width of grid
	}

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			//grid[i][j] 
			grid[i][j] = createTile(color, j, i, size);
			color = (Color){
				(color.r + 20) % 255,
				(color.g + 20) % 255,
				(color.b + 20) % 255,
				255
			};

		}

	}
	
	map.tilesGrid = grid;
	


	return map;

}
Tile createTile(Color color, int widthIndex, int heightIndex, Vector2 tileSize){
	
	Tile tile = {
		.color = color,
		.position = { 1.0f + widthIndex * tileSize.x, 0.0f, 1.0f + heightIndex * tileSize.y },
		.size = tileSize
	};

	
	tile.boundbox = setBoundBox(&tile);

	return tile;

}
BoundingBox setBoundBox(Tile* tile){
	BoundingBox boundBox =  {
		(Vector3){tile->position.x - tile->size.x/2, 0.0f, tile->position.z - tile->size.y/2},
		(Vector3){tile->position.x + tile->size.x/2, 1.0f, tile->position.z + tile->size.y/2}
	};

	return boundBox;
}


void drawTiles(TileMap* map){
	
	for(int i = 0; i < map->mapDim.y; i++){		//height
		for(int j = 0; j < map->mapDim.x; j++){		//width
			Tile tile = map->tilesGrid[i][j];
			DrawPlane(tile.position, tile.size, tile.color);
			if(!DEBUG_MODE) {
				DrawBoundingBox(tile.boundbox,SKYBLUE);
			}
		}
	}

}

void updateTilePosition(Tile* tile, Vector3 newPosition){
	tile->position = newPosition;
	tile->boundbox = setBoundBox(tile);
	
}

RayCollision checkTileCollisions(Tile** tiles,int numOfTiles, Ray ray){
	RayCollision collision;
	for (int i = 0; i < numOfTiles; i++){
		collision = GetRayCollisionBox(ray,(*tiles)[i].boundbox);
		if (collision.hit) break;
	}
	return collision;
}

