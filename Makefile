outbreak: main.o SDLMain.m outbreak.o
	gcc -o outbreak main.o SDLMain.m outbreak.o -framework Cocoa -framework SDL -arch i386

main.o: main.c main.h outbreak.h
	gcc -c main.c -arch i386

outbreak.o: outbreak.c outbreak.h main.h
	gcc -c outbreak.c -arch i386

clean:
	rm outbreak *.o

