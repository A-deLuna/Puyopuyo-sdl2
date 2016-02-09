#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SDL2/SDL.h>

class Input;
class Controller {
public:
  bool was_up_pressed(Input& input);
  bool was_down_pressed(Input& input);
  bool was_left_pressed(Input& input);
  bool was_right_pressed(Input& input);
  bool was_rotate_right_pressed(Input& input);
  bool was_rotate_left_pressed(Input& input);
  Controller(SDL_Scancode up,
             SDL_Scancode down,
             SDL_Scancode left,
             SDL_Scancode right,
             SDL_Scancode rotate_right,
             SDL_Scancode rotate_left);
private:
  SDL_Scancode up;
  SDL_Scancode down;
  SDL_Scancode left;
  SDL_Scancode right;
  SDL_Scancode rotate_right;
  SDL_Scancode rotate_left;
  
};
#endif
