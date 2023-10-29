static-analyze:
	cppcheck --std=c++20 src

OBJS = src/main.cc src/popen.cc

CC = clang++

detected_OS := $(shell uname)

ifeq ($(detected_OS),Darwin)
	CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c++20 -I/opt/homebrew/Cellar/raylib/4.5.0/include -D_THREAD_SAFE -D_RAYLIB_BACKEND
	LFLAGS =  -Iinclude -L/opt/homebrew/Cellar/raylib/4.5.0/lib -lraylib
endif

OBJ_NAME = popen

build : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS)

