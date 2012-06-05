outbreak: ball.o block.o level.o main.o mathy.o object.o outbreak.o palette.o player.o resources.o SDLMain.m
	gcc -o outbreak ball.o block.o level.o main.o mathy.o object.o outbreak.o palette.o player.o resources.o SDLMain.m -framework Cocoa -framework SDL -arch i386

ball.o: ball.c ball.h main.h palette.h object.h
	gcc -c ball.c -arch i386

block.o: block.c block.h main.h palette.h object.h
	gcc -c block.c -arch i386

level.o: level.c level.h main.h palette.h block.h object.h
	gcc -c level.c -arch i386

main.o: main.c main.h palette.h outbreak.h block.h object.h player.h ball.h resources.h
	gcc -c main.c -arch i386

mathy.o: mathy.c mathy.h main.h palette.h
	gcc -c mathy.c -arch i386

object.o: object.c object.h main.h palette.h mathy.h
	gcc -c object.c -arch i386

outbreak.o: outbreak.c outbreak.h main.h palette.h block.h object.h player.h ball.h mathy.h level.h resources.h
	gcc -c outbreak.c -arch i386

palette.o: palette.c palette.h main.h
	gcc -c palette.c -arch i386

player.o: player.c player.h main.h palette.h object.h
	gcc -c player.c -arch i386

resources.o: resources.c resources.h main.h palette.h
	gcc -c resources.c -arch i386

premake:
	ruby premake.rb

clean:
	rm -f *.o outbreak
