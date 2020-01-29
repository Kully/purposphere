FLAGS = -lSDL2 -lm -Og -g

all:
	gcc main.c lib.c $(FLAGS) -o main

play:
	gcc main.c lib.c $(FLAGS) -o main
	./main

clean:
	rm -f main
