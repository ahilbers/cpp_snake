#include <iostream>
#include <deque>
#include "game.h"
#include "objects.h"


namespace objects {


  Snake::Snake(int map_side_length) : map_side_length(map_side_length) {
    // Initialise snake in middle of grid, facing right
    is_alive = true;
    direction = 67;
    head_location = {
      map_side_length * (int)(map_side_length / 2)
      + (int)(map_side_length / 2)
    };
    locations.push_front(head_location);
  };


  void Snake::update_head_location() {
    // Get new location of snake's head

    if (direction == 68) {  // left
      if (head_location % map_side_length == 0) {
        head_location += map_side_length - 1;
      }
      else {
        head_location -= 1;
      }
    }
    else if (direction == 67) {  // right
      if (head_location % map_side_length == map_side_length - 1) {
        head_location -= map_side_length - 1;
      }
      else {
        head_location += 1;
      }
    }
    else if (direction == 65) {  // up
      if (head_location / map_side_length == 0) {
        head_location += (map_side_length - 1) * map_side_length;
      }
      else {
        head_location -= map_side_length;
      }
    }
    else if (direction == 66) {  // down
      head_location += map_side_length;
    };

    // Keep snake on map
    head_location = head_location % (map_side_length * map_side_length);

    // If new head location is in snake, the snake has died
    if (is_at_location(head_location)) {
      is_alive = false;
    }
  }
  

  bool Snake::is_at_location(int location) {
    // Check if any part of the snake is currently at that location
    for (auto i : locations) {
      if (i == location) {
        return true;
      }
    }
    return false;
  }


  std::deque<int> Snake::get_locations() {
    // Get snake's grid locations -- first entry is head, others are body
    return locations;
  };


  void Snake::update_direction(char direction_input) {
    // Update the direction in which snake is travelling
    if (direction == 67 || direction == 68) {
      if (direction_input == 65 || direction_input == 66) {
        direction = direction_input;
      }
    }
    else if (direction == 65 || direction == 66) {
      if (direction_input == 67 || direction_input == 68) {
        direction = direction_input;
      }
    }
  };


  void Snake::update_location(bool grow) {
    // Update snake's locations after step forward
    update_head_location();
    locations.push_front(head_location);
    if (not grow) {
      locations.pop_back();
    } 
  };
  

  Egg::Egg(int map_side_length) : map_side_length(map_side_length) {
    // Initialise egg, two blocks up from middle of grid
    location = {
      map_side_length * ((int)(map_side_length / 2) - 2)
      + (int)(map_side_length / 2)
    };
  }


  int Egg::get_location() {
    return location;
  }


  void Egg::update_location(Snake snake) {
    // Keep suggesting random locations until one is found where snake isn't
    is_valid_new_location = false;
    while (!is_valid_new_location) {
      new_location = rand() % (map_side_length * map_side_length);
      is_valid_new_location = !snake.is_at_location(new_location);
    }
    location = new_location;
  }


  Map::Map(int map_side_length) : map_side_length(map_side_length) {
    // Initialise map via a completly empty map string of the right length
    map_string.insert(0, map_side_length * map_side_length, ' ');
  };


  void Map::update_map_string(Snake snake, Egg egg) {
    // Update string that defines map

    // Reset map string
    for (int i=0; i<map_string.length(); i++) {
      map_string[i] = ' ';
    }

    // Get egg location and add to map
    egg_location = egg.get_location();
    map_string[egg_location] = 'E';

    // Get snake locations and add to map
    snake_locations = snake.get_locations();
    map_string[snake_locations[0]] = 'H';  // Add snake's head
    for (int i=1; i<snake_locations.size(); i++) {
      map_string[snake_locations[i]] = 'S';  // Add snake's body
    };
  };


  void Map::render_horizontal_edge () {
    // Render horizontal edge, used at top and bottom of map
    for (int i=0; i<map_side_length+2; i++) {std::cout << solid_block;};
    std::cout << std::endl << "\r";
  };


  void Map::render(Snake snake, Egg egg) {
    // Render the map with snake and egg on it

    // Get map string from snake and egg
    update_map_string(snake, egg);

    // Render map by printing blocks
    int ms_idx = 0;  // Index that runs through 'map_string'
    char grid_box_item;  // What is in that grid box
    render_horizontal_edge();
    for (int row_num=0; row_num < map_side_length; row_num++) {
      std::cout << solid_block;
      for (int col_num=0; col_num < map_side_length; col_num++) {
        // Render block if snake or egg is there, otherwise space
        grid_box_item = map_string[ms_idx];
        if (grid_box_item == 'E') {
          std::cout << egg_block;
        }
        else if (grid_box_item == 'H') {
          std::cout << solid_block;
        }
        else if (grid_box_item == 'S') {
          std::cout << shade_block;
        }
        else {
          std::cout << space;
        };
        ms_idx++;
      }
      std::cout << solid_block << std::endl << "\r";
    }
    render_horizontal_edge();
    std::cout << "\r" << std::endl;
  };


};
