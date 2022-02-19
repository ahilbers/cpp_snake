#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <deque>
#include <thread>
#include "game.h"  // exit_game, read_user_input, play_game
#include "objects.h"  // Snake, Egg, Map


int main() {
  game::play_game();
  return 0;
};
