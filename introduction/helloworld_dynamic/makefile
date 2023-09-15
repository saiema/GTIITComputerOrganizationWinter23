.PHONY: clean
clean:
	find . -name '*.i' -delete
	find . -name '*.s' -delete
	find . -name '*.o' -delete
	find . -name 'hello' -delete

preprocess: main.c hello.c
	gcc -E -o hello.i hello.c
	gcc -E -o main.i main.c

compile: preprocess
	gcc -S -o hello.s hello.i
	gcc -S -o main.s main.i

assemble: compile
	gcc -c -o hello.o hello.s
	gcc -c -o main.o main.s

link: assemble
	gcc -o hello hello.o main.o