outbreak: main.o SDLMain.m
	gcc -o outbreak main.o SDLMain.m -framework Cocoa -framework SDL -arch i386

main.o: main.c
	gcc -c main.c -arch i386

clean:
	rm outbreak *.o

