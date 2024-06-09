#include <cstdint>
#include <ctime>
#include <string>
#if 0
  g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  ./a.out && rm a.out && exit;
#endif

#include "raylib.h"

static const int SRC_WIDTH = 600;
static const int SRC_HEIGHT = 800;
static const char *APP_NAME = "Sunpp";
static const char *MSG = "Hello!";
static const int FONT_SIZE = 40;
static const int FPS = 60;

// Textures
static const char *SUN_DIR = "./assets/sun.png";

struct Location {
  uint64_t latitude;
  uint64_t longitude;
};

//
struct Weather {
  int temperature;
  time_t date;
  Location location;
  bool rain = false;
  bool snow = false;
  bool cloud = false;
};

struct App {
  Texture2D sun;
};

enum class Picture {
  Sun,
  Cloud,
  Rain,
  Snow,
};

Picture getPicture(Weather weather) {
  if (weather.snow)
    return Picture::Snow;
  if (weather.rain)
    return Picture::Rain;
  if (weather.cloud)
    return Picture::Cloud;
  return Picture::Sun;
}

std::string timeToStr(time_t rawTime) {
  struct tm *timeInfo = localtime(&rawTime);
  char buffer[11]; // "YYYY-MM-DD" is 10 characters plus null terminator
  // Format the date
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);
  return std::string(buffer);
}

std::string locationToStr(Location location) {
  // 51.5072° N, 0.1276°
  if (location.latitude == 515072 && location.longitude == 1276) {
    return std::string("London");
  }
  return std::string("Paris");
}

App initApp() {
  InitWindow(SRC_WIDTH, SRC_HEIGHT, APP_NAME);
  SetTargetFPS(FPS);
  Texture2D sun = LoadTexture(SUN_DIR);
  return App{sun = sun};
}

void drawBackGround(Picture picture, App *app) {
  Texture2D texture;
  switch (picture) {
  case Picture::Sun:
    texture = app->sun;
    break;
  default:
    texture = app->sun;
    break;
  }
  Vector2 position = {0, 0};
  Color tint = WHITE;

  // Draw the texture with the calculated scale
  DrawTextureEx(texture, position, 0.0f, 0.3f, tint);
}

int main() {
  // Init app
  App app = initApp();

  // Main game loop
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawBackGround(Picture::Sun, &app);
    DrawText(MSG, SRC_WIDTH / 3 + 10, SRC_HEIGHT / 5, FONT_SIZE, BLACK);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();
  return 0;
}
