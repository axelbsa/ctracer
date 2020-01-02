#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

#CC=nvcc
# LFLAGS=-lraylib -lGL -lraylib -lglfw3 -lX11 -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
#LFLAGS=-lraylib -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXi -lXcursor -lGL -lGLU -lpthread

# Windows LFLAGS
#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

CC=gcc
CFLAGS=-Wall -std=gnu18 -Wno-missing-braces -ggdb

SOURCES=main.c vec3.c ray.c hitable.c sphere.c hitable_list.c camera.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o main

release:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) -O2 $(LFLAGS) -o main

clean:
	del main
