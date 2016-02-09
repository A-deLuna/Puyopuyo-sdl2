#ifndef PUYO_GAME_HPP
#define PUYO_GAME_HPP

#include <memory>
#include <vector>
#include <random>
#include "graphics.hpp"
#include "controller.hpp"

class Puyo;
class Input;

class PuyoGame {
public:
  PuyoGame(int x_offset, Controller controller);
  ~PuyoGame();
  void update(Input& input);
  void draw(Graphics& graphics);
  void drop_hanging_peices();
  

private:
  void set_falling_peice_in_board();
  void draw_board(Graphics& graphics);
  Graphics::Color get_random_color();
  int dfs_count(int x, int y, Graphics::Color c);
  void dfs_remove(int x, int y, Graphics::Color c);
  bool remove_completed();
  std::shared_ptr<Puyo> get_puyo_at(int x, int y);
  void draw_borders(Graphics& graphics);
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
  Controller controller;
};
#endif
