#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
  enum Color : unsigned int{
    RED = 0xFF0000FF,
    GREEN = 0x00FF00FF,
    BLUE = 0x0000FFFF,
    YELLOW = 0xFFFF00FF,
    PURPLE = 0x663399FF,
    LIGHT_GREY = 0xEEEEEEFF
  };
  Graphics();
  ~Graphics();
  void color(Color c);
  void clear();
  void flip();
  void draw_filled_rect(int x, int y, int h, int w);
  void draw_line(int x1, int y1, int x2, int y2);
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  const int SCREEN_WIDTH = 240;
  const int SCREEN_HEIGHT = 560;
};
#endif
