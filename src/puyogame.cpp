#include "puyogame.hpp"
#include <SDL2/SDL.h>
#include "input.hpp"
#include "puyo.hpp"


PuyoGame::PuyoGame(int x_offset, Controller controller) : 
                                  x_offset(x_offset),
                                  board(BOARD_TILES_X * BOARD_TILES_Y),
                                  gen(rd()), 
                                  dist(0, 4), 
                                  controller(controller){
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
  if (controller.was_down_pressed(input)) {
    if(falling_puyo->can_move_to(0 , 5, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->fall(FALLING_FAST);
    }
  }
  if (controller.was_right_pressed(input)) {
    if(falling_puyo->can_move_to(40 , 0, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->move_right();
    }
  }
  if (controller.was_left_pressed(input)) {
    if(falling_puyo->can_move_to(-40 , 0, BOARD_TILES_X, BOARD_TILES_Y, board)) {
      falling_puyo->move_left();
    }
  }
  if (controller.was_rotate_right_pressed(input)) {
    falling_puyo->rotate_right(BOARD_TILES_X, BOARD_TILES_Y, board);
  }
  if(falling_puyo->can_move_to(0 , 1, BOARD_TILES_X, BOARD_TILES_Y, board)) {
    falling_puyo->fall(FALLING_PER_FRAME);
  }
  else {
    set_falling_peice_in_board();
    drop_hanging_peices();
    while(remove_completed())
      drop_hanging_peices();
  }
}

bool
PuyoGame::remove_completed() {
  bool removed = false;
  for(auto puyo: board) {
    if(puyo) puyo->flag = false;
  }

  for(auto puyo : board) {
    if(puyo && !puyo->flag) {
      int x, y;
      puyo->get_board_XY(x, y);
      int count = dfs_count(x, y, puyo->color);
      if(count >= 4) {
        dfs_remove(x, y, puyo->color);
        removed = true;
      }
    }
  }
  return removed;
}

void
PuyoGame::dfs_remove(int x, int y, Graphics::Color c) {
  if (x < 0
      || x >= BOARD_TILES_X
      || y < 0
      || y >= BOARD_TILES_Y
      || get_puyo_at(x,y) == nullptr
      || get_puyo_at(x, y)->flag == false
      || get_puyo_at(x, y)->color != c) {
    return ;
  }

  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {1, -1, 0, 0};

  get_puyo_at(x,y)->flag = false;

  for(int i = 0; i < 4; i++) {
     dfs_remove(x + dx[i], y + dy[i], c);
  }
  board[y * BOARD_TILES_X + x] = nullptr;
}
int PuyoGame::dfs_count(int x, int y, Graphics::Color c) {
  if (x < 0
      || x >= BOARD_TILES_X
      || y < 0
      || y >= BOARD_TILES_Y
      || get_puyo_at(x,y) == nullptr
      || get_puyo_at(x, y)->flag
      || get_puyo_at(x, y)->color != c) {
    return 0;
  }

  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {1, -1, 0, 0};

  get_puyo_at(x, y)->flag = true;
  int ans = 0;
  for(int i = 0; i < 4; i++) {
    ans += dfs_count(x + dx[i], y + dy[i], c);
  }

  return 1 + ans;
}

std::shared_ptr<Puyo>
PuyoGame::get_puyo_at(int x, int y) {
  return board[y * BOARD_TILES_X + x];
}

void
PuyoGame::drop_hanging_peices() {
  for(int i = BOARD_TILES_Y - 2; i >= 0; i--) {
    for(int j = 0; j < BOARD_TILES_X; j++) {
      std::shared_ptr<Puyo> piece = get_puyo_at(j, i);
      if(piece) {
        board[i * BOARD_TILES_X + j] = nullptr;
        int y = i;
        while(y < BOARD_TILES_Y && get_puyo_at(j, y) == nullptr) {
          y++;
        }
        board[(y-1) * BOARD_TILES_X + j] = piece;
        piece->setXY_from_board(j, y-1);
      }
    }
  }
}

void
PuyoGame::set_falling_peice_in_board() {
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
PuyoGame::draw_borders(Graphics& graphics) {
  int height = BOARD_TILES_Y * 40;
  int width = BOARD_TILES_X * 40;
  graphics.color(Graphics::Color::BLACK);
  // bottom line
  graphics.draw_line(x_offset, height, x_offset + width, height); 

  // left line
  graphics.draw_line(x_offset, 0, x_offset, height);
  // right line
  graphics.draw_line(x_offset + width, 0, x_offset + width, height);
}

void
PuyoGame::draw(Graphics& graphics) {
  if(falling_puyo) falling_puyo->draw(graphics, x_offset);
  draw_board(graphics);
  draw_borders(graphics);
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

