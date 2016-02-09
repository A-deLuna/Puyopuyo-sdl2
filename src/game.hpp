#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "input.hpp"
#include "puyogame.hpp"
#include "controller.hpp"
#include <vector>

class Game {
public:
  Game();
  ~Game();

private:
  void loop();
  void update();
  void draw();
  void draw_background();
  bool process_events();
  
private:
  Graphics graphics;
  Input input;
  Controller left_controller;
  Controller right_controller;
  PuyoGame puyo_game_left;
  PuyoGame puyo_game_right;
};
#endif
