#include "raylib.h"

static const int SRC_WIDTH = 600;
static const int SRC_HEIGHT = 800;
static const char* APP_NAME = "Sunpp";
static const char* MSG = "Hello!";
static const int FONT_SIZE = 40;

int main() {
  // Initialization

  InitWindow(SRC_WIDTH, SRC_HEIGHT, APP_NAME);

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText(MSG, SRC_WIDTH/3 + 10, SRC_HEIGHT/5, FONT_SIZE,
             BLACK);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();  
  return 0;
}
