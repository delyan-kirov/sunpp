#include "app.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <string>

#if 0
 g++ main.cpp -o main ./libapp.so -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  ./main
#endif

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

void drawBackGround(Picture picture, App app) {
  Texture2D texture;
  switch (picture) {
  case Picture::Sun:
    texture = app.sun;
    break;
  default:
    texture = app.sun;
    break;
  }
  Vector2 position = {0, 0};
  Color tint = WHITE;

  // Draw the texture with the calculated scale
  DrawTextureEx(texture, position, 0.0f, 0.3f, tint);
}

#include <dlfcn.h>
// Define the function pointer type for initApp
typedef App (*InitAppFunc)();

// Load the shared library dynamically and obtain the address of the initApp
// function
InitAppFunc loadLibrary(const char *libName) {
  // Load the shared library
  void *libHandle = dlopen(libName, RTLD_LAZY);
  if (!libHandle) {
    // Error handling if library loading fails
    std::cerr << "Error loading library: " << dlerror() << std::endl;
    return nullptr;
  }

  // Obtain address of the initApp function
  InitAppFunc initAppFunc = (InitAppFunc)dlsym(libHandle, "initApp");
  if (!initAppFunc) {
    // Error handling if function address retrieval fails
    std::cerr << "Error getting initApp function address: " << dlerror()
              << std::endl;
    // Unload the library to prevent memory leaks
    dlclose(libHandle);
    return nullptr;
  }

  dlclose(libHandle);
  // Successfully loaded library and obtained function address
  return initAppFunc;
}

typedef void (*Pee)();
Pee loadPee(const char *libName) {
  // Load the shared library
  void *libHandle = dlopen(libName, RTLD_LAZY);
  if (!libHandle) {
    // Error handling if library loading fails
    std::cerr << "Error loading library: " << dlerror() << std::endl;
    return nullptr;
  }

  // Obtain address of the initApp function
  Pee pee = (Pee)dlsym(libHandle, "pee");
  if (!pee) {
    // Error handling if function address retrieval fails
    std::cerr << "Error getting initApp function address: " << dlerror()
              << std::endl;
    // Unload the library to prevent memory leaks
    dlclose(libHandle);
    return nullptr;
  }

  dlclose(libHandle);
  // Successfully loaded library and obtained function address
  return pee;
}

int main() {
  // Init app
  const char *libName = "./libapp.so";

  // Load the initial library
  InitAppFunc initApp = loadLibrary(libName);
  if (!initApp) {
    std::cerr << "Failed to load initial library." << std::endl;
    return 1;
  }

  App app = initApp();

  // Main game loop
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_B)) {
      // Reload the library and reinitialize the App object
      Pee pee = loadPee("./libtest.so");
      if (pee) {
        pee();
      } else {
        std::cerr << "Failed to reload library." << std::endl;
      }
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawBackGround(Picture::Sun, app);
    DrawText(MSG, SRC_WIDTH / 3 + 10, SRC_HEIGHT / 5, FONT_SIZE, BLACK);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();
  return 0;
}
