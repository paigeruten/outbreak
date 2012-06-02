outbreak: main.o outbreak.o palette.o SDLMain.m
	gcc -o outbreak main.o outbreak.o palette.o SDLMain.m -framework Cocoa -framework SDL -arch i386

main.o: main.c main.h palette.h outbreak.h
	gcc -c main.c -arch i386

outbreak.o: outbreak.c outbreak.h main.h palette.h
	gcc -c outbreak.c -arch i386

palette.o: palette.c palette.h main.h
	gcc -c palette.c -arch i386

premake:
	ruby premake.rb

clean:
	rm -f *.o outbreak
