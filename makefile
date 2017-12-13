compiler=g++
flags=-std=c++0x -lncurses
files=main.cc window.cc world.cc

base:
	$(compiler) -o app $(files) $(flags)
debug:
	$(compiler) -o app $(files) $(flags) -g
