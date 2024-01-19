.PHONY: compile
.PHONY: clean
.PHONY: tests

compile: minishell

minishell: minishell.c
	gcc -o minishell minishell.c

tests: minishell
	./minishell "/bin/ls &"
	./minishell "/bin/ls ; /bin/date"
	./minishell "/bin/ls & /bin/date"
	./minishell "/bin/ls > ls.txt"
	cat ls.txt

clean:
	find . -name 'minishell' -delete