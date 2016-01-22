#include "puyo.hpp"
#include "graphics.hpp"
Puyo::Puyo(int x, int y, unsigned int c):
           x(x), y(y), w(PUYO_WIDTH), h(PUYO_HEIGHT), color(c) { }
Puyo::Puyo(int x, int y, int w, int h): x(x), y(y), w(w), h(h) { }

void
Puyo::set_companion(std::shared_ptr<Puyo> companion) {
  this->companion = companion;
}

void
Puyo::draw(Graphics& graphics) {
  graphics.color(color>>24, color>>16, color>>8, color);
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

bool
Puyo::can_move_to(int dx, int dy, int board_x, int board_y,
                  const std::vector<std::shared_ptr<Puyo>>& board) {
  int new_x =  x + dx;
  int new_y = y + dy;
  const int BOARD_WIDTH_IN_PIXELS = board_x * PUYO_WIDTH;
  const int BOARD_HEIGHT_IN_PIXELS = board_y * PUYO_HEIGHT;
  if(new_y + PUYO_HEIGHT > BOARD_HEIGHT_IN_PIXELS) {
    return false;
  }
  if(new_x < 0 || new_x + PUYO_WIDTH > BOARD_WIDTH_IN_PIXELS) return false;
  if(companion) return companion->can_move_to(dx, dy, board_x, board_y, board);
  return true;
}
