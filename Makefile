outbreak: ball.o main.o outbreak.o palette.o player.o SDLMain.m
	gcc -o outbreak ball.o main.o outbreak.o palette.o player.o SDLMain.m -framework Cocoa -framework SDL -arch i386

ball.o: ball.c ball.h main.h
	gcc -c ball.c -arch i386

main.o: main.c main.h palette.h outbreak.h player.h ball.h
	gcc -c main.c -arch i386

outbreak.o: outbreak.c outbreak.h main.h player.h ball.h palette.h controls.h
	gcc -c outbreak.c -arch i386

palette.o: palette.c palette.h main.h
	gcc -c palette.c -arch i386

player.o: player.c player.h main.h
	gcc -c player.c -arch i386

premake:
	ruby premake.rb

clean:
	rm -f *.o outbreak
