#ifndef PUYO_HPP
#define PUYO_HPP

#include <vector>
#include <memory>

#include "graphics.hpp"
class Puyo {
public:
  Puyo(int x, int y, Graphics::Color color);
  Puyo(int x, int y, int w, int h);
  void draw(Graphics& graphics);
  void fall(int pixels);
  void move_left();
  void move_right();
  bool can_move_to(int dx, int dy,
                   int board_x, int board_y,
                   const std::vector<std::shared_ptr<Puyo>>& board);
  void get_board_XY(int& out_x, int& out_y);
  void get_board_XY(int x, int y, int& out_x, int& out_y);
  void setXY(int x, int y);
  void setXY_from_board(int x, int y);
  void rotate_right(std::vector<std::shared_ptr<Puyo>>& board);
  std::shared_ptr<Puyo> companion;

private:
  const int PUYO_WIDTH = 40;
  const int PUYO_HEIGHT = 40;
  int x;
  int y;
  int w;
  int h;
  Graphics::Color color;
};
#endif
