.PHONY: compile
.PHONY: clean

compile: assembleAssembly main.c
	gcc -o simpleFunctions main.c boolean.o math.o strings.o

assembleAssembly: boolean.s math.s strings.s
	gcc -c -fno-PIE boolean.s -o boolean.o
	gcc -c -fno-PIE math.s -o math.o
	gcc -c -fno-PIE strings.s -o strings.o

clean:
	find . -name '*.o' -delete
	find . -name 'simpleFunctions' -delete