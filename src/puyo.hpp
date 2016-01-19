#ifndef PUYO_HPP
#define PUYO_HPP

class Puyo {
public:
  Puyo(int x, int y);
  void set_companion(Puyo* companion);
  int x;
  int y;
private:
  Puyo* companion;
};
#endif
