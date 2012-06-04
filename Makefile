outbreak: ball.o block.o main.o mathy.o outbreak.o palette.o player.o SDLMain.m
	gcc -o outbreak ball.o block.o main.o mathy.o outbreak.o palette.o player.o SDLMain.m -framework Cocoa -framework SDL -arch i386

ball.o: ball.c ball.h main.h
	gcc -c ball.c -arch i386

block.o: block.c block.h main.h palette.h
	gcc -c block.c -arch i386

main.o: main.c main.h palette.h outbreak.h block.h player.h ball.h
	gcc -c main.c -arch i386

mathy.o: mathy.c mathy.h main.h
	gcc -c mathy.c -arch i386

outbreak.o: outbreak.c outbreak.h main.h block.h palette.h player.h ball.h mathy.h
	gcc -c outbreak.c -arch i386

palette.o: palette.c palette.h main.h
	gcc -c palette.c -arch i386

player.o: player.c player.h main.h
	gcc -c player.c -arch i386

premake:
	ruby premake.rb

clean:
	rm -f *.o outbreak
