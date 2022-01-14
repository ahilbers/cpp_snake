#include <iostream>
#include <unistd.h>
#include <vector>
#include <deque>



// std::string get_map_string_from_snake(
//   int map_side_length, std::deque<int> snake
// ) {

//   // Create string defining map, add 'H' at snake's head and 'S' at body points
//   std::string map_string(map_side_length * map_side_length, ' ');
//   map_string[snake[0]] = 'H';
//   for (int i=1; i<snake.size(); i++) {map_string[snake[i]] = 'S'};
  
//   return map_string;
// }





// class Snake {

//   private:
//     int map_side_length;
//     char direction;
//     std::deque<int> locations;

//   public:

//     Snake(int map_side_length) : map_side_length(map_side_length) {
//       direction = 'R';
//       int head_start_location = {
//         map_side_length * (int)(map_side_length / 2)
//         + (int)(map_side_length / 2) 
//         + 1
//       };
//       locations.push_front(head_start_location);
//     };

//     std::deque<int> get_snake_locations() {
//       return locations;
//     };
// };


class Map {

  private:
    const int map_side_length;
    std::string solid_block = "\u2588\u2588";
    std::string shade_block = "\u2593\u2593";
    std::string space = "  ";
    std::string map_string;  // Contains what is at each grid location

    // Render horizontal edge, used at top and bottom of map
    void render_horizontal_edge () {
      for (int i=0; i<map_side_length+2; i++) {std::cout << solid_block;};
      std::cout << std::endl;
    };

  public:

    Map(int map_side_length) : map_side_length(map_side_length) {
      map_string.insert(0, map_side_length * map_side_length, ' ');
    }

    void render() {
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



int main() {

  // int pause = 50000;  // pause in microseconds
  const int map_side_length = 21;  // keep odd so map has a middle

  Map map(map_side_length);
  map.render();


  // std::string map_string;
  // for (int time_step=0; time_step<100; time_step++) {
  //   std::cout << "\x1b[2J\x1b[H";  // clear screen and move cursor to top

  //   // Render the snake
  //   map_string = get_map_string_from_snake(map_side_length, snake);
  //   render_map(map_side_length, map_string);

  //   // Move the snake
  //   head_location = (head_location + 1) % map_side_length;
  //   snake.push_front(head_location);
  //   snake.pop_back();
  //   usleep(pause);
  // }

  

  
  
  
  
  // std::string filled_square = "X";
  // std::string map_string(map_map_side_length * map_map_side_length, ' ');

  // int num_rows = map_map_side_length;
  // int row_length = map_map_side_length;
  // std::string map_string_row;

  

  // for (int step=0; step<map_string.length(); step++) {

  

  //   map_string.replace(step, 1, filled_square);
  //   render_map(map_map_side_length, map_string);
  //   map_string.replace(step, 1, " ");
  //   usleep(pause);
  }