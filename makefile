
CC = gcc
CFLAGS  = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm 


default:  main.o glad.o attractors.o llist.o shader.o setup.o
	$(CC) main.o glad.o attractors.o llist.o shader.o setup.o -o attractors $(CFLAGS)  

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

clean: 
	$(RM) count *.o *~
