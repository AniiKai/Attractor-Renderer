
CC = g++
CFLAGS  = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor


default:  main.o glad.o attractors.o llist.o
	$(CC) main.o glad.o attractors.o llist.o -o attractors $(CFLAGS)  

main.o:  main.cpp 
	$(CC) -c main.cpp

glad.o:  glad.c 
	$(CC) -c glad.c

attractors.o: ./math/attractors.c
	$(CC) -c ./math/attractors.c

llist.o: ./math/llist.c
	$(CC) -c ./math/llist.c

clean: 
	$(RM) count *.o *~
