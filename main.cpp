#include "./queue.hpp"
#include <iostream>
#include <raylib.h>
#include <variant>

#if 0
 g++ main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 ./main; rm ./main; exit
#endif

const int SRC_WIDTH = 600;
const int SRC_HEIGHT = 800;
const int FONT_SIZE = 40;
const int FPS = 60;
const char window_name[20] = "Basic Raylib Window";
const char msg[10] = "Hello!";

struct MouseClick {
  int x;
  int y;
};

struct Key {
  int key;
};

enum class Button {
  Left = 0,
  Right,
};

enum class EventType {
  MouseClicked = 0,
  KeyPressed,
  ButtonClicked,
};

// Use std::variant to hold different event types
using EventData = std::variant<Key, MouseClick, Button>;

struct Event {
  EventType event_type;
  EventData data;

  Event(int key_code)
      : event_type(EventType::KeyPressed), data(Key{key_code}) {}

  Event(int x, int y)
      : event_type(EventType::MouseClicked), data(MouseClick{x, y}) {}

  Event(Button button) : event_type(EventType::ButtonClicked), data(button) {}
};

struct State {
  Color color;
  State() : color(BLACK) {}
};

bool are_colors_equal(Color a, Color b) {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

void handle_events(Queue<Event> &queue, State &state) {
  while (!queue.is_empty()) {
    Event event = queue.dequeue();
    switch (event.event_type) {
    case EventType::MouseClicked: {
      auto mouse_click = std::get<MouseClick>(event.data);
      std::cout << "Mouse clicked at (" << mouse_click.x << ", "
                << mouse_click.y << ")\n";
      break;
    }
    case EventType::KeyPressed: {
      auto key = std::get<Key>(event.data);
      std::cout << "Pressed key: " << key.key << '\n';
      if (key.key == KEY_SPACE) {
        if (are_colors_equal(state.color, RAYWHITE)) {
          state.color = BLACK;
        } else {
          state.color = RAYWHITE;
        }
      }
      break;
    }
    case EventType::ButtonClicked: {
      auto button = std::get<Button>(event.data);
      std::cout << "Button clicked: "
                << (button == Button::Left ? "Left" : "Right") << '\n';
      break;
    }
    }
  }
}

int main() {
  InitWindow(SRC_WIDTH, SRC_HEIGHT, window_name);
  SetTargetFPS(FPS);
  Queue<Event> queue = Queue<Event>();
  State state = State();

  // Main game loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(state.color);
    DrawText(msg, 100, 100, FONT_SIZE, LIGHTGRAY);

    handle_events(queue, state);

    if (IsKeyPressed(KEY_SPACE)) {
      queue.enqueue(Event(KEY_SPACE)); // Key press event
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      queue.enqueue(Event(GetMouseX(), GetMouseY())); // Mouse click event
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
