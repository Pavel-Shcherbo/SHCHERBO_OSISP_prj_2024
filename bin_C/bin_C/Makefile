CC = gcc
CFLAGS = -Wall -Wextra -pthread

SOURCES = main.c
EXECUTABLE = bin_manager

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
		$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
		rm -f $(EXECUTABLE)
	