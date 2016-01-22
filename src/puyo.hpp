#ifndef PUYO_HPP
#define PUYO_HPP

#include <vector>
#include <memory>

class Graphics;
class Puyo {
public:
  Puyo(int x, int y, unsigned int color);
  Puyo(int x, int y, int w, int h);
  void set_companion(std::shared_ptr<Puyo> companion);
  void draw(Graphics& graphics);
  void fall(int pixels);
  void move_left();
  void move_right();
  bool can_move_to(int dx, int dy,
                   int board_x, int board_y,
                   const std::vector<std::shared_ptr<Puyo>>& board);

private:
  std::shared_ptr<Puyo> companion;
  const int PUYO_WIDTH = 40;
  const int PUYO_HEIGHT = 40;
  int x;
  int y;
  int w;
  int h;
  unsigned int color;
};
#endif
