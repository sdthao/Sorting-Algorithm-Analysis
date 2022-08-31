SDL:
	g++ -I src/include -L src/lib -o sort_SDL sort_SDL.cpp -l mingw32 -l SDL2main  -l SDL2

main:
	g++ -std=c++14 main.cpp -o main

clean:
	rm -f main.exe sort_SDL.exe