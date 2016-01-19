#include "game.hpp"
#include <SDL2/SDL.h>

Game::Game() :graphics(), input(), puyo_game() {
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
  puyo_game.draw(graphics);
}

void
Game::update() {
  puyo_game.update(input);
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

