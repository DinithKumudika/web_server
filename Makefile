CC=gcc
TARGET=dist/server

all:
	$(CC) src/main.c src/server.c -o $(TARGET)
clean:
	rm $(TARGET)