.PHONY: compile
.PHONY: clean

compile: test

test: main.c strings.o arrays.o
	gcc -o test main.c strings.o arrays.o

strings.o: strings.s
	gcc -c -o strings.o strings.s

arrays.o: arrays.s
	gcc -c -o arrays.o arrays.s

clean:
	find . -name '*.o' -delete
	find . -name 'nth_letter' -delete