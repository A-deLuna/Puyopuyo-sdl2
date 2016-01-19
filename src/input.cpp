#include "input.hpp"

void
Input::begin_new_frame() {
  pressed_keys.clear();
  released_keys.clear();
}

void
Input::process_event(const SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      key_down(event.key.keysym.scancode);
      break;
    case SDL_KEYUP:
      key_up(event.key.keysym.scancode);
  }
}
void
Input::key_down(SDL_Scancode key) {
  held_keys[key] = true;
  pressed_keys[key] = true;
}

void
Input::key_up(SDL_Scancode key) {
  held_keys[key] = false;
  released_keys[key] = true;
}

bool
Input::was_key_pressed(SDL_Scancode key) {
  return pressed_keys[key];
}

bool
Input::was_key_released(SDL_Scancode key) {
  return released_keys[key];
}

bool
Input::is_key_held(SDL_Scancode key) {
  return released_keys[key];
}

Input::Input() {};
Input::~Input() {};
