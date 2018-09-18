list: simpleCSVsorter.c
	gcc -Wall -Werror -fsanitize=address -o simpleCSVsorter simpleCSVsorter.c
clean:
	rm -f simpleCSVsorter
