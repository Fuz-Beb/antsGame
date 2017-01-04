tp2_a:tp2_a.o tp3_a.o
	gcc -g -o tp2_a tp2_a.o tp3_a.o
tp2_a.o:tp2_a.c
	gcc -g -o tp2_a.o -c tp2_a.c
tp3_a.o:tp3_a.c
	gcc -g -o tp3_a.o -c tp3_a.c


test:
	make
	valgrind ./tp2_a -leak-check=full