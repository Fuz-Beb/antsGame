tp3:tp2_a.o tp3_a.o pile.o
	gcc -g -o tp3 tp2_a.o tp3_a.o pile.o
tp2_a.o:tp2_a.c
	gcc -g -o tp2_a.o -c tp2_a.c
tp3_a.o:tp3_a.c
	gcc -g -o tp3_a.o -c tp3_a.c
pile.o:pile_a_completer.c
	gcc -g -o pile.o -c pile_a_completer.c


test:
	make
	valgrind --leak-check=full --track-origins=yes ./tp3 