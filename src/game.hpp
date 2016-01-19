#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "input.hpp"
#include "puyogame.hpp"
#include <vector>

class Game {
public:
  Game();
  ~Game();

private:
  void loop();
  void update();
  void draw();
  bool process_events();
  
private:
  Graphics graphics;
  Input input;
  PuyoGame puyo_game;
};
#endif
