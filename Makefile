# C Makefile
app: string-utils.o
	cc -o test.out string-utils.o

string-utils.o: string-utils.c
	cc -c string-utils.c

clean:
	rm -f test.out
	rm -f *.o
