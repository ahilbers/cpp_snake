#pragma once

#include "objects.h"

namespace game {
  void start_game(objects::Snake snake, objects::Egg egg, objects::Map map);
  void display_status(int map_side_length, int num_steps, int score);
  void exit_game();
  void read_user_input(int* user_input);
  void play_game();
};
