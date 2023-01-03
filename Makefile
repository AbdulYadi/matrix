.PHONY: clean
matrix: main.o matrix.o
	gcc -o matrix -Wall main.o matrix.o -lm
main.o: main.c
	gcc -c -Wall main.c
matrix.o: matrix.c
	gcc -c -Wall matrix.c
clean:
	rm *.o
