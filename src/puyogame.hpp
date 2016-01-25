#ifndef PUYO_GAME_HPP
#define PUYO_GAME_HPP

#include <memory>
#include <vector>
#include <random>
#include "graphics.hpp"

class Puyo;
class Input;

class PuyoGame {
public:
  PuyoGame(int x_offset);
  ~PuyoGame();
  void update(Input& input);
  void draw(Graphics& graphics);
  void drop_hanging_peices();

private:
  void set_falling_peice_in_board();
  void draw_board(Graphics& graphics);
  Graphics::Color get_random_color();
private:
  const int BOARD_TILES_X = 6;
  const int BOARD_TILES_Y = 14;
  int x_offset;
  std::shared_ptr<Puyo> falling_puyo;
  std::vector<std::shared_ptr<Puyo>> board;
  std::vector<Graphics::Color> colors;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dist;
};
#endif
