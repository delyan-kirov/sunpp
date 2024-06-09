#include <raylib.h>

#if 0
#endif // 0

// Define constants
#define SRC_WIDTH 600
#define SRC_HEIGHT 800
#define APP_NAME "Sunpp"
#define MSG "Hello!"
#define FONT_SIZE 40
#define FPS 60
#define SUN_DIR "./assets/cloud.png"

struct App {
  Texture2D sun;
};

struct App initApp() {
  InitWindow(SRC_WIDTH, SRC_HEIGHT, APP_NAME);
  SetTargetFPS(FPS);
  Texture2D sun = LoadTexture(SUN_DIR);

  struct App app;
  app.sun = LoadTexture(SUN_DIR);
  return app;
}
