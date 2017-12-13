#include <string>

struct player
{
  int x, y;
};

void generate_world(int seed);

char* get_output_game(int width, int height, bool pause);
char* get_output_menu(int width, int height, std::string nr);

int step_right();
int step_left();
int step_up();
int step_down();


