#pragma once

#include <iostream>
#include <deque>
#include "utils.h"


namespace game{


  class Snake {
    private:
      const int map_side_length;
      int direction;  // Integer -- left: 68, right: 67, up: 65, down: 66
      int head_location;
      std::deque<int> locations;
      void update_head_location();
    public:
      Snake(int map_side_length);
      bool is_alive;
      bool is_at_location(int location);
      std::deque<int> get_locations();
      void update_direction(char direction_input);
      void update_location(bool grow_this_round);
  };


  class Egg {
    private:
      const int map_side_length;
      int location;
      int new_location;
      bool is_valid_new_location;
    public:
      Egg(int map_side_length);
      int get_location();
      void update_location(Snake snake);
  };


  class Map {
    private:
      const int map_side_length;
      std::string solid_block = "\u2588\u2588";
      std::string shade_block = "\u2593\u2593";
      std::string egg_block = "()";
      std::string space = "  ";
      std::deque<int> snake_locations;
      int egg_location;
      std::string map_string;  // Contains what is at each grid location
      void update_map_string(Snake snake, Egg egg);
      void render_horizontal_edge();
    public:
      Map(int map_side_length);
      void render(Snake snake, Egg egg);
  };


}
