#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <deque>
#include <thread>
#include "utils.h"  // exit_game, read_user_input
#include "game.h"  // Snake, Egg, Map


void play_game() {

  // Game properties
  int pause = 100000;  // Step length, microseconds
  const int map_side_length = 11;  // keep odd so map has a middle

  // Variables
  game::Snake snake(map_side_length);
  game::Egg egg(map_side_length);
  game::Map map(map_side_length);
  std::deque<int> snake_locations;
  int egg_location;
  int user_input;
  bool grow_this_round;

  user_input = 0;  // Instantiate user input

  // Background thread, reads user input characters
  system("stty raw");  // Set terminal to raw mode, read input without ENTER
  std::thread user_input_stream(utils::read_user_input, &user_input);

  // Play game
  int round_num = 0;
  while (true) {
    std::cout << "\x1b[2J\x1b[H";  // Clear screen and move cursor to top

    // Get variables
    snake_locations = snake.get_locations();
    egg_location = egg.get_location();
    grow_this_round = false;  // Change to true if snake eats egg

    // If snake eats egg, move egg and grow snake
    if (snake_locations[0] == egg_location) {
      egg.update_location(snake);
      grow_this_round = true;
    }

    // Move snake
    snake.update_direction(user_input);
    snake.update_location(grow_this_round);
    map.render(snake, egg);

    round_num++;
    usleep(pause);
  }
};


int main() {
  play_game();
  return 0;
};
