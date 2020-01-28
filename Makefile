FLAGS = -lSDL2 -lm -Og -g #--sanitize=address

all:
	gcc template.c lib.c $(FLAGS) -o template

clean:
	rm -f template
