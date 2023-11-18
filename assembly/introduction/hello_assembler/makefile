.PHONY: compile
.PHONY: clean

compile: hello hello_no_main

hello: hello.s
	gcc -no-pie hello.s -o hello

hello_no_main: hello_no_main.s
	gcc -c -no-pie hello_no_main.s -o hello_no_main.o
	ld --entry=hello -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 hello_no_main.o -o hello_no_main

clean:
	find . -name 'hello' -delete
	find . -name 'hello_no_main' -delete
	find . -name '*.o' -delete
