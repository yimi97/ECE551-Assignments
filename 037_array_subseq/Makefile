myProgram: maxSeq.o test-subseq.o
	gcc -o myProgram maxSeq.o test-subseq.o
test-subseq.o: test-subseq.c
	gcc -std=gnu99 -pedantic -Wall -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc -std=gnu99 -pedantic -Wall -c maxSeq.c
