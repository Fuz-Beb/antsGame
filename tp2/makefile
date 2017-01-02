tp2_a:tp2_a.o
	gcc -g -o tp2_a tp2_a.o
tp2_a.o:tp2_a.c
	gcc -g -o tp2_a.o -c tp2_a.c

test:
	make
	valgrind ./tp2_a -leak-check=full