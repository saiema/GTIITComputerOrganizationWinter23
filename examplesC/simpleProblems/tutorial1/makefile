compile: compile-boolean compile-math compile-strings main.c
	gcc -o tutorial1 main.c boolean.o math.o strings.o

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name 'tutorial1' -delete

compile-boolean: boolean.c standard.h
	gcc -c -o boolean.o boolean.c

compile-math: math.c standard.h
	gcc -c -o math.o math.c

compile-strings: strings.c standard.h
	gcc -c -o strings.o strings.c