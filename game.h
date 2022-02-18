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
      // Snake(int map_side_length) : map_side_length(map_side_length) // TODO: Remove!!
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
      // Egg(int map_side_length) : map_side_length(map_side_length);  // TODO: Remove!!
      int get_location();
      void update_location(Snake snake);
  };


}










// class Map {

//   private:
//     const int map_side_length;
//     std::string solid_block = "\u2588\u2588";
//     std::string shade_block = "\u2593\u2593";
//     std::string egg_block = "()";
//     std::string space = "  ";
//     std::string map_string;  // Contains what is at each grid location
//     std::deque<int> snake_locations;
//     int egg_location;

//     // Update string that defines map
//     void update_map_string(Snake snake, Egg egg) {

//       // Reset map string
//       for (int i=0; i<map_string.length(); i++) {
//         map_string[i] = ' ';
//       }

//       // Get egg location and add to map
//       egg_location = egg.get_location();
//       map_string[egg_location] = 'E';

//       // Get snake locations and add to map
//       snake_locations = snake.get_locations();
//       map_string[snake_locations[0]] = 'H';  // Add snake's head
//       for (int i=1; i<snake_locations.size(); i++) {
//         map_string[snake_locations[i]] = 'S';  // Add snake's body
//       };

//     };

//     // Render horizontal edge, used at top and bottom of map
//     void render_horizontal_edge () {
//       for (int i=0; i<map_side_length+2; i++) {std::cout << solid_block;};
//       std::cout << std::endl << "\r";
//     };

//   public:
//     Map(int map_side_length) : map_side_length(map_side_length) {
//       map_string.insert(0, map_side_length * map_side_length, ' ');
//     }
//     void render(Snake snake, Egg egg) {
//       update_map_string(snake, egg);
      
//       int ms_idx = 0;  // Index that runs through 'map_string'
//       char grid_box_item;  // What is in that grid box

//       // Render map by printing blocks
//       render_horizontal_edge();
//       for (int row_num=0; row_num < map_side_length; row_num++) {
//         std::cout << solid_block;
//         for (int col_num=0; col_num < map_side_length; col_num++) {
//           // Render block if snake or egg is there, otherwise space
//           grid_box_item = map_string[ms_idx];
//           if (grid_box_item == 'E') {
//             std::cout << egg_block;
//           }
//           else if (grid_box_item == 'H') {
//             std::cout << solid_block;
//           }
//           else if (grid_box_item == 'S') {
//             std::cout << shade_block;
//           }
//           else {
//             std::cout << space;
//           };
//           ms_idx++;
//         }
//         std::cout << solid_block << std::endl << "\r";
//       }
//       render_horizontal_edge();
//       std::cout << "\r" << std::endl;

//     };
// };
