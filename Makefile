# C Makefile
app: oshilib.o
	gcc -shared -o liboshi.so oshilib.o

oshilib.o: oshilib.c
	gcc -c -Wall -Werror -fpic oshilib.c

clean:
	rm -f liboshi.so
	rm -f *.o
