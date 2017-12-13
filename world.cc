#include "world.h"
#include <stdlib.h>
#include <string>
#include <cmath>

char* world;
player p1;

int sizex = 1000;
int sizey = 1000;

enum bioms
  {
    grassland, forest, lake, mountain
  };

void generate_world(int seed)
{
  srand(seed);

  int region_count = 100;
  
  bioms region[100];
  for(int i = 0; i < sizex/region_count; i++)
    {
      for(int j = 0; j < sizey/region_count; j++)
	{
	  int r_val = rand() % 10;
	  if(i == 0 && j == 0)
	    {
	      region[i + j*sizex/region_count] = grassland;
	    }
	  else if(i < 2 && j < 2)
	    {
	      if(r_val % 2 == 0)
		{
		  region[i + j*sizex/region_count] = grassland;
		}
	      else
		{
		  region[i + j*sizex/region_count] = forest;
		}
	    }
	  else if(i < 5 && j < 5)
	    {
	      if(r_val % 3 == 0)
		{
		  region[i + j*sizex/region_count] = grassland;
		}
	      else if(r_val % 3 == 1)
		{
		  region[i + j*sizex/region_count] = lake;
		}
	      else
		{
		  region[i + j*sizex/region_count] = forest;
		}
	    }
	  else
	    {
	      if(r_val % 4 == 0)
		{
		  region[i + j*sizex/region_count] = grassland;
		}
	      else if(r_val % 4 == 1)
		{
		  region[i + j*sizex/region_count] = lake;
		}
	      else if(r_val % 4 == 2)
		{
		  region[i + j*sizex/region_count] = mountain;
		}
	      else
		{
		  region[i + j*sizex/region_count] = forest;
		}
	    }
	}
    }
  
  world = new char[sizex*sizey];
  for(int i = 0; i < sizex; i++)
    {
      for(int j = 0; j < sizey; j++)
	{
	  int val = rand()%100;

	  if(i == 0 || j == 0 || i == sizex - 1 || j == sizey - 1)
	    {
	      world[i + j*sizex] = 'M';
	    }
	  else
	    {
	      int ii = i / 100;
	      int jj = j / 100;
	      int chance = rand() % 100;
	      int temp;
	      switch(region[ii + jj * (sizex/100)])
		{
		case(grassland):
		  
		  if(chance < 3)
		    world[i + j*sizex] = 'T';
		  else
		    world[i + j*sizex] = '.';
		  break;
		case(forest):
		  if(chance < 30)
		    world[i + j*sizex] = 'T';
		  else
		    world[i + j*sizex] = '.';
		  break;
		case(lake):
		  ii = (i % 100) > 50 ? (i % 100) : 100 - (i % 100);
		  jj = (j % 100) > 50 ? (j % 100) : 100 - (j % 100);
		  ii -= 50;
		  jj -= 50;
		  temp = abs((ii + jj));
		  temp *= temp;
		  chance = rand() % 5000;
		  if(chance > temp)
		    world[i + j*sizex] = '~';
		  else
		    world[i + j*sizex] = '.';
		  break;
		case(mountain):
		  world[i + j*sizex] = 'M';
		  break;
		default:
		  world[i + j*sizex] = 'E';
		  break;
		}
	    }
	}
    }

  p1.x = 2;
  p1.y = 3;
}

char* get_output_game(int width, int height, bool pause)
{
  char* out = new char[width*height];

  int starth = p1.y - height/2;
  int startw = p1.x - width/2;

  starth = starth >= 0 ? starth : 0;
  startw = startw >= 0 ? startw : 0;

  starth = starth < sizey - height ? starth : sizey - height;
  startw = startw < sizex - width ? startw : sizex - width;

  int ii = 0;
  int jj = 0;
  
  for(int i = starth; i < starth + height; i++)
    {
      for(int j = startw; j < startw + width; j++)
	{
	  out[jj + ii*width] = world[j + i*sizex];

	  if(i == p1.y && j == p1.x)
	    out[jj + ii*width] = 'P';
	  
	  jj++;
	}
      jj = 0;
      ii++;
    }

  std::string bot("Player is at: ");

  std::string x = std::to_string(p1.x);
  std::string y = std::to_string(p1.y);
  
  bot = bot + x + std::string(",") + y;

  if(pause)
    {
      bot += " GAME PAUSED, \'q\' to quit game";
    }

  for(int i = bot.size() - 1; i < width; i++)
    bot += " ";

  for(int i = 0; i < width; i++)
    {
	out[i + (height - 1)*width] = bot[i];
    }
  
  return out;
}

char* get_output_menu(int width, int height, std::string nr)
{
    char* out = new char[width*height];

    std::string welcome("WELCOME TO THE ROUGELIKE");
    std::string info("Start the game with \'s\', pause with \'p\' and exit the game with \'q\'");

    std::string seed("World seed(default 1): ");
    seed += nr;
    
    int start = width/2 - welcome.length()/2;
    int stop = start + welcome.length();

    int ii = 0;

    for(int i = 0; i < width*height; i++)
      out[i] = ' ';
    
    for(int i = start; i < stop; i++)
      {
	out[width*((height/2) - 1) + i] = welcome[ii];
	ii++;
      }

    start = width/2 - info.length()/2;
    stop = start + info.length();

    ii = 0;
    
    for(int i = start; i < stop; i++)
    {
    	out[width*(height/2) + i] = info[ii];
    	ii++;
    }

    start = width/2 - seed.length()/2;
    stop = start + seed.length();

    ii = 0;
    
    for(int i = start; i < stop; i++)
    {
    	out[width*(height/2 + 1) + i] = seed[ii];
    	ii++;
    }
    
    return out;
}

int step_right()
{
  if(p1.x + 1 < sizex - 1)
    {
      if(world[p1.x + p1.y*sizex + 1] == '.')
	p1.x += 1;
    }
}
int step_left()
{
  if(p1.x - 1 >= 0)
    {
      if(world[p1.x + p1.y*sizex - 1] == '.')
	p1.x -= 1;
    }
}
int step_up()
{
  if(p1.y - 1 >= 0)
    {
      if(world[p1.x + (p1.y - 1) * sizex] == '.')
	p1.y -= 1;
    }
}
int step_down()
{
    if(p1.y + 1 < sizey - 1)
    {
      if(world[p1.x + (p1.y + 1) * sizex] == '.')
	p1.y += 1;
    }
}
