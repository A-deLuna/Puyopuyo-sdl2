#include "puyogame.hpp"
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "input.hpp"
#include "puyo.hpp"

PuyoGame::PuyoGame() : board(BOARD_TILES_X * BOARD_TILES_Y){
}

PuyoGame::~PuyoGame() {
}

void
PuyoGame::update(Input& input) {
  const int FALLING_PER_FRAME = 1;
  const int FALLING_FAST = 5;

  if(falling_puyo == nullptr) {
    falling_puyo = std::make_shared<Puyo>(40, 0, Graphics::Color::GREEN);
    falling_puyo->companion = std::make_shared<Puyo>(80, 0, Graphics::Color::BLUE);
  }
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
  else {
    set_falling_peice_in_board();
  }
}

void PuyoGame::set_falling_peice_in_board() {
  int x, y;
  falling_puyo->get_board_XY(x, y);
  board[y * BOARD_TILES_X + x] = falling_puyo;
  falling_puyo->companion->get_board_XY(x, y);
  board[y * BOARD_TILES_X + x] = falling_puyo->companion;
  falling_puyo->companion = nullptr;
  falling_puyo = nullptr;
}

void
PuyoGame::draw(Graphics& graphics) {
  draw_background(graphics);
  if(falling_puyo) falling_puyo->draw(graphics);
  draw_board(graphics);
  graphics.flip();
}
void
PuyoGame::draw_board(Graphics& graphics) {
  for(auto puyo: board) {
    if(puyo) {
      puyo->draw(graphics);
    }
  }
}

void
PuyoGame::draw_background(Graphics& graphics) {
  graphics.color(Graphics::Color::LIGHT_GREY);
  graphics.clear();
}
