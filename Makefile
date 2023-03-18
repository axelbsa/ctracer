#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

#CC=nvcc
# LFLAGS=-lraylib -lGL -lraylib -lglfw3 -lX11 -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
#LFLAGS=-lraylib -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXi -lXcursor -lGL -lGLU -lpthread

# Windows LFLAGS
#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

CC=clang

ifeq ($(OS),Windows_NT)
    CFLAGS=-Wall -std=gnu18 -Wno-missing-braces -O3 -ffast-math
    RMCMD=del
else
    CFLAGS=-Wall -std=gnu18 -Wno-missing-braces -ggdb -Wall
    LDFLAGS=-lm
    RMCMD=rm
endif


SOURCES=src/main.c src/vec3.c src/ray.c src/material.c src/sphere.c src/hitable_list.c src/camera.c src/common.c

all:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o main

release:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) -O3 $(LFLAGS) -o main

clean:
	$(RMCMD) main
