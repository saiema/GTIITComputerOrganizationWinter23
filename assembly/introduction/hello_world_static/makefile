.PHONY: compile

compile: hello

hello: strings.o main.c
	gcc -o hello main.c strings.o

strings.o: strings.s
	gcc -c -fno-PIE strings.s -o strings.o

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name 'hello' -delete