.PHONY: compile
.PHONY: clean

compile: and or xor not

and: and.s
	gcc -c -no-pie and.s -o and.o
	ld --entry=and -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 and.o -o and

or: or.s
	gcc -c -no-pie or.s -o or.o
	ld --entry=or -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 or.o -o or

xor: xor.s
	gcc -c -no-pie xor.s -o xor.o
	ld --entry=xor -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 xor.o -o xor

not: not.s
	gcc -c -no-pie not.s -o not.o
	ld --entry=not -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 not.o -o not
	

clean:
	find . -name 'and' -delete
	find . -name 'or' -delete
	find . -name 'xor' -delete
	find . -name 'not' -delete
	find . -name '*.o' -delete
