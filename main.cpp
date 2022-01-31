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


class Snake {

  private:

    int map_side_length;
    char direction;
    int head_location;
    std::deque<int> locations;

    void update_head_location() {
      if (direction == 'L') {
        if (head_location % map_side_length == 0) {
          head_location += map_side_length - 1;
        }
        else {
          head_location -= 1;
        }
      }
      else if (direction == 'R') {
        if (head_location % map_side_length == map_side_length - 1) {
          head_location -= map_side_length - 1;
        }
        else {
          head_location += 1;
        }
      }
      else if (direction == 'U') {
        if (head_location / map_side_length == 0) {
          head_location += (map_side_length - 1) * map_side_length;
        }
        else {
          head_location -= map_side_length;
        }
      }
      else if (direction == 'D') {
        head_location += map_side_length;
      };

      // Keep the snake on the map
      head_location = head_location % (map_side_length * map_side_length);
    }

  public:

    Snake(int map_side_length) : map_side_length(map_side_length) {
      // Initialise snake, in the middle of the grid and facing right
      direction = 'R';
      head_location = {
        map_side_length * (int)(map_side_length / 2)
        + (int)(map_side_length / 2)
      };
      locations.push_front(head_location-1);
      locations.push_front(head_location);
    };

    void update_direction(char direction_input) {
      if (direction == 'L' || direction == 'R') {
        if (direction_input == 'U' || direction_input == 'D') {
          direction = direction_input;
        }
      }
      else if (direction == 'U' || direction == 'D') {
        if (direction_input == 'L' || direction_input == 'R') {
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
      
    }

    // Get snake's grid locations -- first entry is head, others are body
    std::deque<int> get_locations() {
      return locations;
    };


};


class Map {

  private:
    const int map_side_length;
    std::string solid_block = "\u2588\u2588";
    std::string shade_block = "\u2593\u2593";
    std::string space = "  ";
    std::string map_string;  // Contains what is at each grid location

    // Update string that defines map
    void update_map_string(Snake snake) {

      // Reset map string
      for (int i=0; i<map_string.length(); i++) {
        map_string[i] = ' ';
      }

      // Get snake's locations and add them
      std::deque<int> snake_locations = snake.get_locations();
      map_string[snake_locations[0]] = 'H';  // Add snake's head
      for (int i=1; i<snake_locations.size(); i++) {
        map_string[snake_locations[i]] = 'S';  // Add snake's body
      };
    };

    // Render horizontal edge, used at top and bottom of map
    void render_horizontal_edge () {
      for (int i=0; i<map_side_length+2; i++) {std::cout << solid_block;};
      std::cout << std::endl;
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
        std::cout << solid_block << std::endl;
      }
      render_horizontal_edge();
      

    };
};


void play_game_orig() {

  // Map properties
  const int map_side_length = 11;  // keep odd so map has a middle

  // Run properties
  int pause = 1000000;  // pause in microseconds
  int num_ts = 10;

  char command;
  std::deque<int> command_list;

  Snake snake(map_side_length);
  Map map(map_side_length);
  bool grow;

  for (int step=0; step<num_ts; step++) {
    std::cout << "\x1b[2J\x1b[H";  // clear screen and move cursor to top
    map.render(snake);
    grow = step % 8 == 0;
    if (step % 7 == 2) {snake.update_direction('U');}
    snake.update_location(grow);
    usleep(pause);
  }
}


// Read user input characters 
void read_user_input(char* user_input_pointer) {
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
  int pause = 1000000;  // Step length, microseconds

  // Variables
  char user_input;

  // Instantiate user input
  user_input = '0';

  // Create a thread that always runs and reads in user input characters
  std::thread user_input_stream(read_user_input, &user_input);
  
  // Every step, print number of steps and user input -- '0' if none entered
  int i = 0;
  while (true) {
    std::cout << "Tick " << i << ", value " << user_input << "\r" << std::endl;
    user_input = '0';  // Reset value
    usleep(pause);
    i++;
  }

  user_input_stream.join();
};


int main() {
  play_game();
  return 0;
};
