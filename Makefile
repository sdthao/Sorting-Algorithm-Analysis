all:
	g++ -I src/include -L src/lib -o sort_SDL sort_SDL.cpp -l mingw32 -l SDL2main  -l SDL2