#include "controller.hpp"
#include "input.hpp"
Controller::Controller(SDL_Scancode up,
                       SDL_Scancode down,
                       SDL_Scancode left,
                       SDL_Scancode right,
                       SDL_Scancode rotate_right,
                       SDL_Scancode rotate_left) : 
                       up(up),
                       down(down),
                       left(left),
                       right(right),
                       rotate_right(rotate_right),
                       rotate_left(rotate_left){}


bool
Controller::was_up_pressed(Input& input) {
  return input.was_key_pressed(up);
}
bool
Controller::was_down_pressed(Input& input) {
  return input.was_key_pressed(down);
}
bool
Controller::was_left_pressed(Input& input) {
  return input.was_key_pressed(left);
}
bool
Controller::was_right_pressed(Input& input) {
  return input.was_key_pressed(right);
}
bool
Controller::was_rotate_right_pressed(Input& input) {
  return input.was_key_pressed(rotate_right);
}
bool
Controller::was_rotate_left_pressed(Input& input) {
  return input.was_key_pressed(rotate_left);
}
