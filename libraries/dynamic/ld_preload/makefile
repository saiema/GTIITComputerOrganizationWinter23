.PHONY: compile
compile: echo

echo: custom_puts.so main.c
	gcc -o echo main.c

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.so' -delete
	find . -name 'echo' -delete

custom_puts.so: custom_puts.c
	gcc -shared -fpic -o custom_puts.so custom_puts.c -ldl