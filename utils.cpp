#include <iostream>
#include "utils.h"


namespace utils {

  void exit_game() {
    system("stty cooked");  // Return terminal to normal (not "raw") mode
    std::cout << std::endl;
    exit(0);
  };

  void read_user_input(int* user_input) {
    while(true) {
      *user_input = getchar();
      if (*user_input == '.') {
        exit_game();  // Quit when '.' is pressed
      }
    }
  };

}
