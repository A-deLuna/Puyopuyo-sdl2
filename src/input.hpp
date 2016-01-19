#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <map>

class Input {
public:
  Input();
  ~Input();
  void begin_new_frame();
  void process_event(const SDL_Event& event);

  bool was_key_pressed(SDL_Scancode key);
  bool was_key_released(SDL_Scancode key);
  bool is_key_held(SDL_Scancode key);

private:
  void key_down(SDL_Scancode key);
  void key_up(SDL_Scancode key);
private:
  std::map<SDL_Scancode, bool> held_keys;
  std::map<SDL_Scancode, bool> pressed_keys;
  std::map<SDL_Scancode, bool> released_keys;
};
#endif
