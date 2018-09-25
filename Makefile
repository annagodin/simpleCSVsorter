all: simpleCSVsorter.c mergesort.o

simpleCSVsorter: simpleCSVsorter.o mergesort.o
	gcc -Wall -o simpleCSVsorter simpleCSVsorter.o mergesort.o
mergesort.o: mergesort.c
	gcc -c mergesort.c
clean:
	rm -f simpleCSVsorter mergesort.o
