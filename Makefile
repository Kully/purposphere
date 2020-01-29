FLAGS = -lSDL2 -lm -Og -g

all:
	gcc src/main.c src/lib.c $(FLAGS) -o main
	./main

clean:
	rm -f main
