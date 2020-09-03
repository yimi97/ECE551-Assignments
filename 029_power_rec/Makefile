myProgram: power.o test-power.o
	gcc -o myProgram power.o test-power.o
test-power.o: test-power.c power.c
	gcc -std=gnu99 -pedantic -Wall -c test-power.c
power.o: power.c
	gcc -std=gnu99 -pedantic -Wall -c power.c
