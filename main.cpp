#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <deque>
#include <thread>


void print_vector(std::vector<char> mydeque) {
  for (auto i : mydeque) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}


void print_deque(std::deque<int> mydeque) {
  for (auto i : mydeque) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}


class Egg {

  private:
    const int map_side_length;
    int location;

  public:
    Egg(int map_side_length) : map_side_length(map_side_length) {
      // Initialise egg, two blocks up from the middle of the grid
      location = 
    }

  
    
}


class Snake {

  private:
    const int map_side_length;
    int direction;  // Use integers for direction (left: 68, right: 67, up: 65, down: 66)
    int head_location;
    std::deque<int> locations;
    void update_head_location() {
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
    }

  public:
    Snake(int map_side_length) : map_side_length(map_side_length) {
      // Initialise snake, in the middle of the grid and facing right
      direction = 67;
      head_location = {
        map_side_length * (int)(map_side_length / 2)
        + (int)(map_side_length / 2)
      };
      locations.push_front(head_location-1);
      locations.push_front(head_location);
    };
    void update_direction(char direction_input) {
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
    void update_location(bool grow=false) {
      // Update snake's location deque after a step forward
      update_head_location();
      locations.push_front(head_location);
      if (not grow) {
        locations.pop_back();
      } 
    };
    std::deque<int> get_locations() {
      // Get snake's grid locations -- first entry is head, others are body
      return locations;
    };

};


class Map {

  private:
    const int map_side_length;
    std::string solid_block = "\u2588\u2588";
    std::string shade_block = "\u2593\u2593";
    std::string egg_block = "\u25d6\u25d6";
    std::string space = "  ";
    std::string map_string;  // Contains what is at each grid location

    // Update string that defines map
    void update_map_string(Snake snake) {

      // Reset map string
      for (int i=0; i<map_string.length(); i++) {
        map_string[i] = ' ';
      }

      // Get snake locations and add them
      std::deque<int> snake_locations = snake.get_locations();
      map_string[snake_locations[0]] = 'H';  // Add snake's head
      for (int i=1; i<snake_locations.size(); i++) {
        map_string[snake_locations[i]] = 'S';  // Add snake's body
      };

      // Get egg location and add to map
      print_deque(snake_locations);
      std::cout << "\n" << std::endl << "\r";

    };

    // Render horizontal edge, used at top and bottom of map
    void render_horizontal_edge () {
      for (int i=0; i<map_side_length+2; i++) {std::cout << solid_block;};
      std::cout << std::endl << "\r";
    };

  public:

    Map(int map_side_length) : map_side_length(map_side_length) {
      map_string.insert(0, map_side_length * map_side_length, ' ');
    }

    void render(Snake snake) {
      update_map_string(snake);
      render_horizontal_edge();
      int ms_idx = 0;  // Index that runs through 'map_string'
      char grid_box_item;  // What is in that grid box
      for (int row_num=0; row_num < map_side_length; row_num++) {
        std::cout << solid_block;
        for (int col_num=0; col_num < map_side_length; col_num++) {
          // Render block if snake is there, otherwise space
          grid_box_item = map_string[ms_idx];
          if (grid_box_item == 'H') {std::cout << solid_block;}
          else if (grid_box_item == 'S') {std::cout << shade_block;}
          else {std::cout << space;};
          ms_idx++;
        }
        std::cout << solid_block << std::endl << "\r";
      }
      render_horizontal_edge();
      

    };
};


// Read user input characters 
void read_user_input(int* user_input_pointer) {
  system("stty raw");  // Set terminal to raw mode, read input without ENTER
  while(true) {
    *user_input_pointer = getchar();
    if (*user_input_pointer == '.') { // Terminate when '.' is pressed
      system("stty cooked");  // Return terminal to normal mode
      std::cout << std::endl;
      exit(0);
    }
  }
}


void play_game() {

  // Game properties
  int pause = 100000;  // Step length, microseconds
  const int map_side_length = 15;  // keep odd so map has a middle

  // Variables
  int user_input;
  bool grow_this_round;
  Snake snake(map_side_length);
  Map map(map_side_length);

  // Instantiate user input
  user_input = 0;

  // Create thread that always runs and reads in user input characters
  std::thread user_input_stream(read_user_input, &user_input);
  

  
  

  int round_num = 0;
  while (true) {
    std::cout << "\x1b[2J\x1b[H";  // clear screen and move cursor to top
    // grow_this_round = {round_num %8 == 0};
    grow_this_round = false;
    snake.update_direction(user_input);
    snake.update_location(grow_this_round);
    map.render(snake);
    std::cout << "\r" << std::endl;
    round_num++;
    usleep(pause);
  }
};


int main() {
  play_game();
  return 0;
};
