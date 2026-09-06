CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
GLFLAGS = -lglfw -lGL -ldl -lm

SRC = src/main.cpp src/gl.c
OUT = doom_game

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(GLFLAGS)

clean:
	rm -f $(OUT)



