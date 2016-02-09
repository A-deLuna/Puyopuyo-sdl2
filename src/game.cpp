#include "game.hpp"
#include <SDL2/SDL.h>
#include "controller.hpp"

Game::Game() : left_controller(SDL_SCANCODE_W,
                             SDL_SCANCODE_S,
                             SDL_SCANCODE_A,
                             SDL_SCANCODE_D,
                             SDL_SCANCODE_T,
                             SDL_SCANCODE_Y), 
               right_controller(SDL_SCANCODE_UP,
                             SDL_SCANCODE_DOWN,
                             SDL_SCANCODE_LEFT,
                             SDL_SCANCODE_RIGHT,
                             SDL_SCANCODE_O,
                             SDL_SCANCODE_P), 
                puyo_game_left(50, left_controller),
                puyo_game_right(500, right_controller) {
  loop();
}

Game::~Game() {
  SDL_Quit();
}

void
Game::loop() {
  const int FPS = 60;
  const int SKIP_TICKS = 1000 / FPS;
  long next_game_tick = SDL_GetTicks();
  long sleep_time;
  while(true) {
    if (process_events()) break;
    update();
    draw();

    next_game_tick += SKIP_TICKS;
    sleep_time = next_game_tick - SDL_GetTicks();
    if(sleep_time >= 0) {
      SDL_Delay(sleep_time);
    }
  }
}

void
Game::draw() {
  draw_background();
  puyo_game_left.draw(graphics);
  puyo_game_right.draw(graphics);
}

void
Game::update() {
  puyo_game_left.update(input);
  puyo_game_right.update(input);
}
void
Game::draw_background() {
  graphics.color(Graphics::Color::LIGHT_GREY);
  graphics.clear();
}

bool
Game::process_events() {
  SDL_Event event;
  input.begin_new_frame();
  while (SDL_PollEvent(&event)) {
    input.process_event(event);
    switch (event.type) {
      case SDL_QUIT:
        return true;
        break;
    }
  }
  return false;
}

