#include "puyogame.hpp"
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "input.hpp"
#include "puyo.hpp"

PuyoGame::PuyoGame() {
  falling_puyo = new Puyo(50, 0);
}

PuyoGame::~PuyoGame() {
  delete falling_puyo;
}

void
PuyoGame::update(Input& input) {
  const int falling_per_frame = 1;
  if (input.was_key_pressed(SDL_SCANCODE_DOWN)) {
    falling_puyo->y++;
  }
  if (input.was_key_pressed(SDL_SCANCODE_RIGHT)) {
    falling_puyo->x+=50;
  }
  if (input.was_key_pressed(SDL_SCANCODE_LEFT)) {
    falling_puyo->x-=50;
  }
  falling_puyo->y += falling_per_frame;
}

void
PuyoGame::draw(Graphics& graphics) {
  graphics.color(238, 238, 238, 255);
  graphics.clear();
  graphics.color(255, 0, 0, 255);
  graphics.draw_filled_rect(falling_puyo->x, falling_puyo->y, 50, 50);
  graphics.flip();
}
