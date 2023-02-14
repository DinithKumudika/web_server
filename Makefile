CC=gcc
TARGET=dist/server

all:
	$(CC) src/main.c src/server.c src/request.c -o $(TARGET)
clean:
	rm $(TARGET)