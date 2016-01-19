#include "puyo.hpp"

Puyo::Puyo(int x, int y): x(x), y(y) { }

void
Puyo::set_companion(Puyo* companion) {
  this->companion = companion;
}
