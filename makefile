
CC = gcc
WCC = x86_64-w64-mingw32-gcc

CFLAGS  = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm 
WFLAGS = -I/mingw64/include/ -L/mingw64/lib -lglfw3dll -lopengl32

default:  main.o glad.o attractors.o llist.o shader.o setup.o
	$(CC) main.o glad.o attractors.o llist.o shader.o setup.o -o arch64 $(CFLAGS)  
windows: wmain.o wglad.o wattractors.o wllist.o wshader.o wsetup.o
	$(WCC) main.o glad.o attractors.o llist.o shader.o setup.o -o win64.exe $(WFLAGS)

main.o:  main.c
	$(CC) -c main.c

glad.o:  glad.c 
	$(CC) -c glad.c

attractors.o: ./math/attractors.c
	$(CC) -c ./math/attractors.c

llist.o: ./math/llist.c
	$(CC) -c ./math/llist.c

shader.o: ./shader/shader.c
	$(CC) -c ./shader/shader.c

setup.o: ./misc/setup.c
	$(CC) -c ./misc/setup.c

wmain.o:  main.c
	$(WCC) -c main.c

wglad.o:  glad.c 
	$(WCC) -c glad.c

wattractors.o: ./math/attractors.c
	$(WCC) -c ./math/attractors.c

wllist.o: ./math/llist.c
	$(WCC) -c ./math/llist.c

wshader.o: ./shader/shader.c
	$(WCC) -c ./shader/shader.c

wsetup.o: ./misc/setup.c
	$(WCC) -c ./misc/setup.c

clean: 
	$(RM) count *.o *~
