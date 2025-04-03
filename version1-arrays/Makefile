all: PhotoLab PhotoLabTest

PhotoLab: PhotoLab.o FileIO.o DIPs.o Advanced.o
	gcc PhotoLab.o FileIO.o DIPs.o Advanced.o -o PhotoLab -lm

PhotoLabTest: PhotoLabTEST.o FileIO.o DIPs.o Advanced.o
	gcc PhotoLabTEST.o FileIO.o DIPs.o Advanced.o -o PhotoLabTest -lm

PhotoLab_v2.o: PhotoLab.c FileIO.h DIPs.h Advanced.h
	gcc -c -std=c11 -Wall PhotoLab.c -o PhotoLab_v2.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -c -std=c11 -Wall FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -c -std=c11 -Wall DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -c -std=c11 -Wall Advanced.c -o Advanced.o

PhotoLabTEST.o: PhotoLab.c
	gcc -D DEBUG -c PhotoLab.c -o PhotoLabTEST.o

clean:
	rm -f *.o PhotoLab
