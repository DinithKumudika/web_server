CC=gcc
TARGET=dist/server

all:
	$(CC) src/main.c src/server.c src/request.c src/response.c -o $(TARGET)
clean:
	rm $(TARGET)