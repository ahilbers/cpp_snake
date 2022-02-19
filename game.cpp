#include <unistd.h>
#include <thread>
#include "game.h"  // exit_game, read_user_input, play_game
#include "objects.h"  // Snake, Egg, Map


namespace game {

  void start_game(objects::Snake snake, objects::Egg egg, objects::Map map) {
    // Prepare game -- give user instructions on how to start
    std::cout << "\x1b[2J\x1b[H";  // Clear screen and move cursor to top
    map.render(snake, egg);
    std::cout << "TO START: TYPE 'P' + ENTER" << std::endl;
    std::cout << "TO QUIT WHILE PLAYING: TYPE 'Q'" << std::endl;
    int start;
    std::cin >> start;
  }


  void display_status(int map_side_length, int num_steps, int score) {
    // Display status, number of steps and score
    std::string whitespace((int)(map_side_length / 2 + 1), ' ');
    std::cout << std::endl;
    std::cout << whitespace << "\u2588 STEPS  " << num_steps << "\r" << std::endl;
    std::cout << whitespace << "\u2588 SCORE  " << score << "\r" << std::endl;
    std::cout << std::endl;
  }


  void exit_game() {
    system("stty cooked");  // Return terminal to normal (not "raw") mode
    std::cout << std::endl;
    exit(0);
  };


  void read_user_input(int* user_input) {
    // Background thread used to read direction commands in gameplay
    while(true) {
      *user_input = getchar();
      if (*user_input == 'q') {
        exit_game();  // Quit when '.' is pressed
      }
    }
  };


  void play_game() {

    // Game properties
    int pause = 100000;  // Step length, microseconds
    const int map_side_length = 11;  // keep odd so map has a middle

    // Variables
    objects::Snake snake(map_side_length);
    objects::Egg egg(map_side_length);
    objects::Map map(map_side_length);
    std::deque<int> snake_locations;
    int egg_location;
    int user_input;
    bool grow_this_round;
    int num_steps;
    int score;

    start_game(snake, egg, map);

    // Background thread, reads user input characters
    system("stty raw");  // Set terminal to raw mode, read input without ENTER
    user_input = 0;  // Instantiate user input
    std::thread user_input_stream(game::read_user_input, &user_input);

    // Play game
    num_steps = 0;
    score = 0;
    while (snake.is_alive) {
      std::cout << "\x1b[2J\x1b[H";  // Clear screen and move cursor to top

      // Get variables
      snake_locations = snake.get_locations();
      egg_location = egg.get_location();
      grow_this_round = false;  // Change to true if snake eats egg

      // If snake eats egg, move egg and grow snake
      if (snake_locations[0] == egg_location) {
        egg.update_location(snake);
        grow_this_round = true;
        score++;
      }

      // Move snake
      snake.update_direction(user_input);
      snake.update_location(grow_this_round);
      map.render(snake, egg);

      display_status(map_side_length, num_steps, score);

      num_steps++;
      usleep(pause);
    };

    // If snake has died, end the game
    std::cout << "GAME OVER" << std::endl;
    game::exit_game();
  };

}
