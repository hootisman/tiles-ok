#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>


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


BoundingBox setBoundBox(Tile* tile){
	BoundingBox boundBox =  {
		(Vector3){tile->position.x - tile->size.x/2, 0.0f, tile->position.z - tile->size.y/2},
		(Vector3){tile->position.x + tile->size.x/2, 0.0f, tile->position.z + tile->size.y/2}
	};

	return boundBox;
}
Tile createTile(){
	
	Tile tile = {
		.color = DARKGREEN,
		.position = { 1.0f, 0.0f, 1.0f },
		.size = { 2.0f, 2.0f }
	};

	
	tile.boundbox = setBoundBox(&tile);

	return tile;

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

void drawTiles(Tile** tiles, int numOfTiles){
	
	for(int i = 0; i < numOfTiles; i++){
		Tile tile = (*tiles)[i];
		DrawPlane(tile.position, tile.size, tile.color);
		DrawBoundingBox(tile.boundbox,SKYBLUE);
	}

}


int main(){
	const int screenWidth = 800;
	const int screenHeight = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth,screenHeight, "hi");
	
	Camera3D camera = {0};
	camera.position = (Vector3){0.0f,10.0f,10.0f};
	camera.target = (Vector3){0.0f,0.0f,0.0f};
	camera.up = (Vector3){0.0f,1.0f,0.0f};
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	SetCameraMode(camera,CAMERA_FREE);

	Tile* tiles = malloc(sizeof(Tile) * 5);
	int numOfTiles = 2;

	tiles[0] = createTile();
	tiles[1] = createTile();

	updateTilePosition(&tiles[1],(Vector3){ 3.0f, 0.0f, 1.0f });


//	Ray playerRay = { 0 };
//	RayCollision rayCollision = { 0 };
	


	SetTargetFPS(60);

	while (!WindowShouldClose()){

		UpdateCamera(&camera);
		
/*
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			if (!rayCollision.hit){
				playerRay = GetMouseRay(GetMousePosition(), camera);
				rayCollision = checkTileCollisions(&tiles, numOfTiles, playerRay);
			}else rayCollision.hit = false;

		}
*/

		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
/*
		if (rayCollision.hit){
			Vector3 collisionV = rayCollision.point;
		       	printf("%f,%f,%f\n",collisionV.x,collisionV.y,collisionV.z);
			rayCollision.hit = false;
		}
*/
		BeginMode3D(camera);
			
		drawTiles(&tiles, numOfTiles);
//		DrawRay(playerRay,MAROON);
			
		EndMode3D();


		DrawFPS(10,10);
		EndDrawing();
		
	}
	CloseWindow();
	return 0;
}

