all:
	g++ -I src/include -L src/lib -o snake snake.cpp -lmingw32 -lSDL2main -lSDL2
	