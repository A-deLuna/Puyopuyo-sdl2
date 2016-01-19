#ifndef PUYO_GAME_HPP
#define PUYO_GAME_HPP

class Puyo;
class Input;
class Graphics;

class PuyoGame {
public:
  PuyoGame();
  ~PuyoGame();
  void update(Input& input);
  void draw(Graphics& graphics);
private:
  Puyo* falling_puyo;
};
#endif
