.PHONY: compile
.PHONY: clean

compile: multiply

multiply: main.c russian_peasant.s
	gcc -no-pie main.c russian_peasant.s -o multiply

clean:
	find . -name 'multiple' -delete