.PHONY: compile
compile: system

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name 'system' -delete

system: system.o out.o main.o sstd.h
	gcc -o system system.o out.o main.o -I.

system.o: system.c sstd.h
	gcc -c -o system.o system.c -I.

out.o: out.c sstd.h
	gcc -c -o out.o out.c -I.

main.o: main.c sstd.h
	gcc -c -o main.o main.c -I.