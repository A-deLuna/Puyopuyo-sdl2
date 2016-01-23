#include "puyo.hpp"
Puyo::Puyo(int x, int y, Graphics::Color c):
           x(x), y(y), w(PUYO_WIDTH), h(PUYO_HEIGHT), color(c) { }
Puyo::Puyo(int x, int y, int w, int h): x(x), y(y), w(w), h(h) { }

void
Puyo::draw(Graphics& graphics) {
  graphics.color(color);
  graphics.draw_filled_rect(x, y, h, w);
  if(companion) companion->draw(graphics);
}

void
Puyo::fall(int pixels) {
  y += pixels;
  if(companion) companion->fall(pixels);
}

void Puyo::move_left() {
  x -= PUYO_WIDTH;
  if(companion) companion->move_left();
}
void Puyo::move_right() {
  x += PUYO_WIDTH;
  if(companion) companion->move_right();

}

void
Puyo::get_board_XY(int& out_x, int& out_y) {
  out_x = x / PUYO_WIDTH;
  // round up integer division
  out_y = (y + PUYO_HEIGHT - 1) / PUYO_HEIGHT;
}

void
Puyo::get_board_XY(int x, int y, int& out_x, int& out_y) {
  out_x = x / PUYO_WIDTH;
  // round up integer division
  out_y = (y + PUYO_HEIGHT - 1) / PUYO_HEIGHT;
}

bool
Puyo::can_move_to(int dx, int dy, int board_x, int board_y,
                  const std::vector<std::shared_ptr<Puyo>>& board) {
  int new_x =  x + dx;
  int new_y = y + dy;

  int new_board_x, new_board_y;
  get_board_XY(new_x, new_y, new_board_x, new_board_y);

  const int BOARD_WIDTH_IN_PIXELS = board_x * PUYO_WIDTH;
  const int BOARD_HEIGHT_IN_PIXELS = board_y * PUYO_HEIGHT;

  // check bottom
  if(new_y + PUYO_HEIGHT > BOARD_HEIGHT_IN_PIXELS) {
    return false;
  }
  // check left and right borders
  if(new_x < 0 || new_x + PUYO_WIDTH > BOARD_WIDTH_IN_PIXELS) return false;

  // check if theres a peice where we want to move
  if(board[new_board_y * board_x + new_board_x] != nullptr) {
    return false;
  }

  if(companion) return companion->can_move_to(dx, dy, board_x, board_y, board);
  return true;
}
