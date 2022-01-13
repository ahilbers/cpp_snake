#include <iostream>
#include <unistd.h>
#include <vector>
#include <deque>


void print_vector(std::vector<int> vector) {
  for (int i=0; i<vector.size(); i++) {
    std::cout << vector[i] << " ";
  }
  std::cout << std::endl;
}


void render_map(int map_side_length, std::string map_string) {

  // To make map appear more square, each grid square is 2x1 characters
  int row_char_length = 2 * map_side_length;
  int num_rows = map_side_length;
  std::string block = "\u2588\u2588";

  // Duplicate each character in 'map_string' to make it work with 2x1 grid
  std::string render_map_string(row_char_length * num_rows, ' ');
  for (int i=0; i<row_char_length*num_rows; i++){
    render_map_string[2*i] = map_string[i];
    render_map_string[2*i+1] = map_string[i];
  }

  // Render a horizontal edge, used at top and bottom of map
  auto render_horizontal_edge = [](int map_side_length, std::string block) {
    for (int i=0; i<map_side_length+2; i++) std::cout << block;
    std::cout << std::endl;
  };

  // Render the map by printing the string in rows of length 'row_length'
  std::string map_string_row(row_char_length, ' ');
  render_horizontal_edge(map_side_length, block);
  int pos_of_x;
  for (int row_num=0; row_num<num_rows; row_num++) {
    map_string_row = {
      render_map_string.substr(row_num * row_char_length, row_char_length)
    };
    pos_of_x = map_string_row.find('X');
    if (pos_of_x != -1) {
      map_string_row.replace(pos_of_x+1, 1, "\u2588");
      map_string_row.replace(pos_of_x, 1, "\u2588");
    }  
    std::cout << block << map_string_row << block << std::endl;
  }
  render_horizontal_edge(map_side_length, block);
  std::cout << std::endl;
}


void render_map_new(int side_length, std::string map_string) {

  // Define grid blocks or spaces. 2 characters are roughly square shape
  std::string block = "\u2588\u2588";   // Solid block
  std::string shade_block = "\u2592\u2592";   // Shaded block
  std::string space = "  ";  // Empty space

  // Render horizontal edge, used at top and bottom of map
  auto render_horizontal_edge = [](int side_length, std::string block) {
    for (int row_num=0; row_num < side_length+2; row_num++) {
      std::cout << block;
    };
    std::cout << std::endl;
  };

  render_horizontal_edge(side_length, block);

  int ms_idx = 0;  // Index that runs through 'map_string'
  char grid_box_item;  // What is in that grid box
  for (int row_num=0; row_num < side_length; row_num++) {
    std::cout << block;
    for (int col_num=0; col_num < side_length; col_num++) {

      // Render a block if the snake is there, otherwise a space
      grid_box_item = map_string[ms_idx];
      if (grid_box_item == 'H') {std::cout << block;}
      else if (grid_box_item == 'S') {std::cout << shade_block;}
      else {std::cout << space;};
      ms_idx++;
    }
    std::cout << block;
    std::cout << std::endl;
  }

  render_horizontal_edge(side_length, block);

}


std::string get_map_string_from_snake(int side_length, std::deque<int> snake) {

  // Create string that defines the map
  int map_string_length = side_length * side_length;
  std::string map_string(map_string_length, ' ');
  
  int m_idx;  // Index used for map_string

  // Add 'H' at the snake's head
  m_idx = snake[0];
  map_string[m_idx] = 'H';

  // Add 'S' at the snake's other locations
  
  for (int s_idx=1; s_idx < snake.size(); s_idx++) {
    m_idx = snake[s_idx];
    map_string[m_idx] = 'S';
  }

  return map_string;
}







int main() {

  int pause = 100000;  // pause in microseconds
  int side_length = 10;

  std::deque<int> snake;
  snake.push_front(0);
  snake.push_front(1);
  snake.push_front(2);
  snake.push_front(3);

  std::string map_string = get_map_string_from_snake(side_length, snake);
  render_map_new(side_length, map_string);

  
  
  
  
  // std::string filled_square = "X";
  // std::string map_string(map_side_length * map_side_length, ' ');

  // int num_rows = map_side_length;
  // int row_length = map_side_length;
  // std::string map_string_row;

  

  // for (int step=0; step<map_string.length(); step++) {

  //   std::cout << "\x1b[2J\x1b[H";  // clear screen and move cursor to top

  //   map_string.replace(step, 1, filled_square);
  //   render_map(map_side_length, map_string);
  //   map_string.replace(step, 1, " ");
  //   usleep(pause);
  }