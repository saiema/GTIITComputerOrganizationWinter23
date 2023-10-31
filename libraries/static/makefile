LIBDIR          = ./stdLib/

.PHONY: compile
compile: demo
demo: $(LIBDIR)libstd.a $(LIBDIR)standard.h main.c
	gcc main.c -o demo -L$(LIBDIR) -I$(LIBDIR) -l std

$(LIBDIR)libstd.a: $(LIBDIR)boolean.o $(LIBDIR)math.o $(LIBDIR)strings.o $(LIBDIR)standard.h
	ar rcs $(LIBDIR)libstd.a $(LIBDIR)boolean.o $(LIBDIR)math.o $(LIBDIR)strings.o

$(LIBDIR)boolean.o: $(LIBDIR)boolean.c $(LIBDIR)standard.h
	gcc -c $(LIBDIR)boolean.c -I$(LIBDIR) -o $@

$(LIBDIR)math.o: $(LIBDIR)math.c $(LIBDIR)standard.h
	gcc -c $(LIBDIR)math.c -I$(LIBDIR) -o $@

$(LIBDIR)strings.o: $(LIBDIR)strings.c $(LIBDIR)standard.h
	gcc -c $(LIBDIR)strings.c -I$(LIBDIR) -o $@

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.a' -delete
	find . -name 'demo' -delete