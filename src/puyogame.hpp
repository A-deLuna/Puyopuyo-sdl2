#ifndef PUYO_GAME_HPP
#define PUYO_GAME_HPP

#include <memory>
#include <vector>

class Puyo;
class Input;
class Graphics;

class PuyoGame {
public:
  PuyoGame();
  ~PuyoGame();
  void update(Input& input);
  void draw(Graphics& graphics);
  void draw_background(Graphics& graphics);

private:
  void set_falling_peice_in_board();
  void draw_board(Graphics& graphics);
private:
  const int BOARD_TILES_X = 6;
  const int BOARD_TILES_Y = 14;
  std::shared_ptr<Puyo> falling_puyo;
  std::vector<std::shared_ptr<Puyo>> board;
};
#endif
