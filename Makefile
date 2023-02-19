CC=gcc
SRCDIR=src
TARGET=bin/server

all:
	$(CC) $(SRCDIR)/main.c $(SRCDIR)/server.c $(SRCDIR)/request.c $(SRCDIR)/response.c -o $(TARGET)
clean:
	rm $(TARGET)