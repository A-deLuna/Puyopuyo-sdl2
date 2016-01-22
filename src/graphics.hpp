#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
  enum Color : unsigned int{
    RED = 0xFF0000FF,
    GREEN = 0x00FF00FF,
    BLUE = 0x0000FFFF
  };
  Graphics();
  ~Graphics();
  void color(char r, char g, char b, char a);
  void clear();
  void flip();
  void draw_filled_rect(int x, int y, int h, int w);
  void draw_line(int x1, int y1, int x2, int y2);
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  const int SCREEN_WIDTH = 940;
  const int SCREEN_HEIGHT = 880;
};
#endif
