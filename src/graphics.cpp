#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <sstream>
Graphics::Graphics() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::stringstream msg;
    msg << "SDL_Init Error: "  << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  SDL_CreateWindowAndRenderer(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    0,
    &window,
    &renderer
  );
  if (nullptr == window || nullptr == renderer) {
    std::stringstream msg;
    msg << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
}

Graphics::~Graphics() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void
Graphics::color(char r, char g, char b, char a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void
Graphics::draw_filled_rect(int x, int y, int h, int w) {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.h = h;
  rect.w = w;
  SDL_RenderFillRect(renderer, &rect);
}

void
Graphics::draw_line(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void
Graphics::clear() {
  SDL_RenderClear(renderer);
}

void
Graphics::flip() {
  SDL_RenderPresent(renderer);
}
