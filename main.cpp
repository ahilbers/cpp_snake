#include <iostream>
#include <unistd.h>
#include <vector>


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


int main() {

  // std::string filled_square = "\u2588";  // filled rectangle

  int pause = 100000;  // pause in microseconds
  int map_side_length = 8;
  std::string filled_square = "X";
  std::string map_string(map_side_length * map_side_length, ' ');

  int num_rows = map_side_length;
  int row_length = map_side_length;
  std::string map_string_row;

  

  for (int step=0; step<map_string.length(); step++) {

    std::cout << "\x1b[2J\x1b[H";  // clear screen and move cursor to top

    map_string.replace(step, 1, filled_square);
    render_map(map_side_length, map_string);
    map_string.replace(step, 1, " ");
    usleep(pause);
  }



  
  
  
  // std::string map_string_row;
  // std::cout << '+' << horizontal_edge << '+' << std::endl;
  // for (int row_num=0; row_num<map_side_length; row_num++) {
  //   map_string_row = map_string_repeated.substr(row_num * map_side_length, 2*map_side_length);
  //   std::cout << '|' << map_string_row << '|' << std::endl;
  // }
  // std::cout << '+' << horizontal_edge << '+' << std::endl;




  // for (int i=0; i<10; i++) {
  
  //   sleep(pause);
  //   printf("%d\n", i);
  // };
  // return 0;
}





// #include <iostream>
// #include <string.h>
// #include <math.h>
// #include <unistd.h>
// using namespace std;

// int _main() {
//     float A = 0, B = 0;
//     float i, j;
//     int k;
//     float z[1760];
//     char b[1760];
//     printf("\x1b[2J");
//     for(;;) {
//         memset(b,32,1760);
//         memset(z,0,7040);
//         for(j=0; j < 6.28; j += 0.07) {
//             for(i=0; i < 6.28; i += 0.02) {
//                 float c = sin(i);
//                 float d = cos(j);
//                 float e = sin(A);
//                 float f = sin(j);
//                 float g = cos(A);
//                 float h = d + 2;
//                 float D = 1 / (c * h * e + f * g + 5);
//                 float l = cos(i);
//                 float m = cos(B);
//                 float n = sin(B);
//                 float t = c * h * g - f * e;
//                 int x = 40 + 30 * D * (l * h * m - t * n);
//                 int y= 12 + 15 * D * (l * h * n + t * m);
//                 int o = x + 80 * y;
//                 int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
//                 if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
//                     z[o] = D;
//                     b[o] = "...,,,ooo000"[N > 0 ? N : 0]; //works much better with ".,-~:;=!*#$@" or "JackEatDonut"
//                 }
//             }
//         }
//         printf("\x1b[H");
//         for(k = 0; k < 1761; k++) {
//             putchar(k % 80 ? b[k] : 10);
//             A += 0.00004;
//             B += 0.00002;
//         }
//         usleep(30000);
//     }
//     return 0;
// }
