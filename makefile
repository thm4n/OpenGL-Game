GLFW_FLAGS = -I/home/thman/opt/glfw/include -I/home/opt/glfw/deps/glad
INC_FLAGS = -ISource -ISource/Dependencies -ISource/Game -ISource/ogl 
LIBS_FLAGS = -lglfw3 -lglfw -lrt -lGLU -lGL -lm -lglut -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama
CFLAGS = -g -Wall -Werror -Wextra

FLAGS = ${GLFW_FLAGS} ${LIBS_FLAGS} ${CFLAGS}

SRC = $(shell find . -type f -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

glad.o:
	g++ -c ~/opt/glad/src/glad.c -o glad.o ${FLAGS}

%.o: %.cpp
	g++ -c -o $@ $^ ${FLAGS}


run: build
	./Game

	
build: ${OBJ} glad.o
	g++ $^ -o ./Game ${FLAGS}

clean:
	rm -f ${OBJ}
	rm -f ./Game
