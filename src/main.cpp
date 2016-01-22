#include <SDL2/SDL.h>
#include "game.hpp"


int main() {
  Game game;

  atexit(SDL_Quit);
  return 0;
}
