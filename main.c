#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiles.h"

bool DEBUG_MODE = 0;	//1 if in debug mode, 0 if not

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

	
	TileMap map = createTileMap((Vector2){2.0f, 2.0f}, (Vector2){100.0f, 100.0f});
	

//	Ray playerRay = { 0 };
//	RayCollision rayCollision = { 0 };
	


	SetTargetFPS(60);

	while (!WindowShouldClose()){

		if (IsKeyPressed(KEY_F3)){ DEBUG_MODE = !DEBUG_MODE; }

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
			
		drawTiles(&map);
//		DrawRay(playerRay,MAROON);
			
		EndMode3D();

		if (DEBUG_MODE) { DrawFPS(10,10); }


		EndDrawing();
		
	}
	CloseWindow();
	return 0;
}

