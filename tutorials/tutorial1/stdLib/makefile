compile: boolean.o strings.o math.o main.c
	gcc -o tutorial1 main.c boolean.o math.o strings.o

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name 'tutorial1' -delete

boolean.o: boolean.c standard.h
	gcc -c -o boolean.o boolean.c

math.o: math.c standard.h
	gcc -c -o math.o math.c

strings.o: strings.c standard.h
	gcc -c -o strings.o strings.c