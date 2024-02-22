.PHONY = all clean
FLAGS = -Wall -g

all: StrList

#creating library

StrList.o: StrList.c StrList.h
	gcc -c $(FLAGS) StrList.c -o StrList.o

Main.o: Main.c StrList.h
	gcc -c $(FLAGS) Main.c -o Main.o

StrList: StrList.o Main.o
	gcc $(FLAGS) StrList.o Main.o -o StrList

#
clean:
	rm -f StrList *.o *.so *.a


	