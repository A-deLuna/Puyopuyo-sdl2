#include "puyogame.hpp"
#include <SDL2/SDL.h>
#include "input.hpp"
#include "puyo.hpp"

PuyoGame::PuyoGame(int x_offset) :x_offset(x_offset), board(BOARD_TILES_X * BOARD_TILES_Y), gen(rd()), dist(0, 4){
  colors = {
    Graphics::Color::RED,
    Graphics::Color::GREEN,
    Graphics::Color::BLUE,
    Graphics::Color::YELLOW,
    Graphics::Color::PURPLE
  };
}

PuyoGame::~PuyoGame() {
}

Graphics::Color 
PuyoGame::get_random_color() {
  return colors[dist(gen)];
}

void
PuyoGame::update(Input& input) {
  const int FALLING_PER_FRAME = 1;
  const int FALLING_FAST = 5;

  if(falling_puyo == nullptr) {
    falling_puyo = std::make_shared<Puyo>(40, 0, get_random_color());
    falling_puyo->companion = std::make_shared<Puyo>(80, 0, get_random_color());
  }
  if (input.was_key_pressed(SDL_SCANCODE_DOWN)) {
    if(falling_puyo->can_move_to(0 , 5, BOARD_TILES_X, BOARD_TILES_Y, board)) {
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
  if (input.was_key_pressed(SDL_SCANCODE_Z)) {
    falling_puyo->rotate_right(board);
  }
  if(falling_puyo->can_move_to(0 , 1, BOARD_TILES_X, BOARD_TILES_Y, board)) {
    falling_puyo->fall(FALLING_PER_FRAME);
  }
  else {
    set_falling_peice_in_board();
    drop_hanging_peices();
  }
}

void PuyoGame::drop_hanging_peices() {
  for(int i = BOARD_TILES_Y - 2; i >= 0; i--) {
    for(int j = 0; j < BOARD_TILES_X; j++) {
      std::shared_ptr<Puyo> piece = board[i * BOARD_TILES_X + j];
      if(piece) {
        board[i * BOARD_TILES_X + j] = nullptr;
        int y = i;
        while(y < BOARD_TILES_Y && board[y * BOARD_TILES_X + j] == nullptr) {
          y++;
        }
        board[(y-1) * BOARD_TILES_X + j] = piece;
        piece->setXY_from_board(j, y-1);
      }
    }
  }
}

void PuyoGame::set_falling_peice_in_board() {
  int x, y;
  falling_puyo->get_board_XY(x, y);
  board[y * BOARD_TILES_X + x] = falling_puyo;
  falling_puyo->setXY_from_board(x, y);
  falling_puyo->companion->get_board_XY(x, y);
  falling_puyo->companion->setXY_from_board(x, y);
  board[y * BOARD_TILES_X + x] = falling_puyo->companion;
  falling_puyo->companion = nullptr;
  falling_puyo = nullptr;
}

void
PuyoGame::draw(Graphics& graphics) {
  if(falling_puyo) falling_puyo->draw(graphics, x_offset);
  draw_board(graphics);
  graphics.flip();
}
void
PuyoGame::draw_board(Graphics& graphics) {
  for(auto puyo: board) {
    if(puyo) {
      puyo->draw(graphics, x_offset);
    }
  }
}

