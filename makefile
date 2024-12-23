OFILES=main.o  grid_display.o window.o snake.o linkedList.o errors.o
FLAGS=-g -Wall -Wextra -Wvla -Werror -fsanitize=address,undefined

main: $(OFILES)
	gcc -O0 $(OFILES) $(FLAGS) -o main -lm -lSDL2 -lSDL2_ttf

main.o: main.c
	gcc -c -g main.c

grid_display.o: WINDOW_HANDLING/grid_display.c
	gcc -c -g WINDOW_HANDLING/grid_display.c

window.o: WINDOW_HANDLING/window.c
	gcc -c -g WINDOW_HANDLING/window.c

snake.o: snake.c
	gcc -c -g snake.c

linkedList.o: UTILS/linkedList.c
	gcc -c -g UTILS/linkedList.c

errors.o: UTILS/errors.c
	gcc -c -g UTILS/errors.c
clean:
	rm -rf main *.o
