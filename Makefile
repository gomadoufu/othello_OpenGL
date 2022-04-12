ifeq ($(OS),Windows_NT)
	LIBS = -lfreeglut -lopengl32
else
	LIBS = -framework GLUT -framework OpenGL
endif
CC = g++

all: othello debug test
othello: main.cpp othello.cpp display.cpp
	$(CC) main.cpp othello.cpp display.cpp -o run.exe $(LIBS)
debug: debug.cpp othello.cpp
	$(CC) debug.cpp othello.cpp -o debug
test: animation_test.cpp
	$(CC) animation_test.cpp -o animation_test $(LIBS)