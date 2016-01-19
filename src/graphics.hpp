#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
  Graphics();
  ~Graphics();
  void color(int r, int g, int b, int a);
  void clear();
  void flip();
  void draw_filled_rect(int x, int y, int h, int w);
  void draw_line(int x1, int y1, int x2, int y2);
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
};
#endif
