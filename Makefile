.SUFFIXES: .c .h .o
all: interro Main


#interro:interro.c
#Main:main.c

.c.o:
	gcc -c $<


interro: interro.c table.o fonctions_lecture.o
	gcc -lpthread -o $@ $^
 
Main: main.c table.o fonctions_lecture.o
	gcc -lpthread -lm -o $@ $^


table.o: table.h
fonctions_lecture.o:fonctions_lecture.h


clean:
	rm -f *.o
	rm -f *~
