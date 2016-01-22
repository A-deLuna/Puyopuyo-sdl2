#include "puyogame.hpp"
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "input.hpp"
#include "puyo.hpp"

PuyoGame::PuyoGame() : board(BOARD_TILES_X * BOARD_TILES_Y){
  falling_puyo = std::make_shared<Puyo>(50, 0, Graphics::Color::GREEN);
  falling_puyo->set_companion(std::make_shared<Puyo>(100,0, Graphics::Color::BLUE));
}

PuyoGame::~PuyoGame() {
}

void
PuyoGame::update(Input& input) {
  const int FALLING_PER_FRAME = 1;
  const int FALLING_FAST = 5;
  if (input.was_key_pressed(SDL_SCANCODE_DOWN)) {
    if(falling_puyo->can_move_to(0 , 1, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->fall(FALLING_FAST);
    }
  }
  if (input.was_key_pressed(SDL_SCANCODE_RIGHT)) {
    if(falling_puyo->can_move_to(40 , 0, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->move_right();
    }
  }
  if (input.was_key_pressed(SDL_SCANCODE_LEFT)) {
    if(falling_puyo->can_move_to(-40 , 0, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->move_left();
    }
  }
  if(falling_puyo->can_move_to(0 , 1, BOARD_TILES_X, BOARD_TILES_Y, board)) {
    falling_puyo->fall(FALLING_PER_FRAME);
  }
}

void
PuyoGame::draw(Graphics& graphics) {
  draw_background(graphics);
  falling_puyo->draw(graphics);
  graphics.flip();
}

void 
PuyoGame::draw_background(Graphics& graphics) {
  graphics.color(238, 238, 238, 255);
  graphics.clear();
}
