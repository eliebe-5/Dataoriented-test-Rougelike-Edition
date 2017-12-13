#include <ncurses.h>
#include <string>
#include "window.h"
#include "world.h"

state game_state;

int w, h;

std::string seed("");

void init()
{
  initscr();
  w = getmaxx(stdscr);
  h = getmaxy(stdscr);
  raw();
  noecho();
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  game_state = menu;
}

void start_game()
{
  game_state = game;
  
  generate_world(std::stoi(seed));
}

int update()
{
  char* out;
  
  if(game_state == game)
    out = get_output_game(w, h, false);
  else if(game_state == pause)
    out = get_output_game(w, h, true);
  else
    out = get_output_menu(w, h, seed);
  
  move(0, 0);

  for(int i = 0; i < w*h; i++)
    {
      if(out[i] == 'M')
	{
	  attron(COLOR_PAIR(3));
	  printw("%c", out[i]);
	  attroff(COLOR_PAIR(3));
	}
      else if(out[i] == '~')
	{
	  attron(COLOR_PAIR(2));
	  printw("%c", out[i]);
	  attroff(COLOR_PAIR(2));
	}
      else if(out[i] == 'T' || out[i] == '.')
	{
	  attron(COLOR_PAIR(1));
	  printw("%c", out[i]);
	  attroff(COLOR_PAIR(1));
	}
      else
	{
	  attron(COLOR_PAIR(4));
	  printw("%c", out[i]);
	  attroff(COLOR_PAIR(4));
	}
      
    }
  delete[] out;
  refresh();
  if(input()) return 0;
  return 1;
}

void end()
{
  endwin();
}

int input()
{
  int c = getch();

  if(c == 47)
    return 1;

  if(game_state == game)
    {
      switch(c)
	{
	case('p'):
	  game_state = pause;
	  break;
	case(KEY_RIGHT):
	  step_right();
	  break;
	case(KEY_LEFT):
	  step_left();
	  break;
	case(KEY_UP):
	  step_up();
	  break;
	case(KEY_DOWN):
	  step_down();
	  break;
	default:
	  return 0;
	  break;
	}
    }
  else if(game_state == pause)
    {
      switch(c)
	{
	case('p'):
	  game_state = game;
	  break;
	case('q'):
	  return 1;
	  break;

	}
    }
  else if(game_state == menu)
    {
      switch(c)
	{
	case('s'):
	  start_game();
	  break;
	case('q'):
	  return 1;
	  break;
	}
      
      if(c >= '0' && c <= '9' && !(c == '0' && seed.length() == 0) && seed.length() < 9)
	{
	  seed += (char)c;
	}
    }
  return 0;
}
