CC = gcc
CFLAGS = -Wall -Wextra -pthread

SOURCES = main.c binCommands.c logActions.c menu.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = bin_manager

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(EXECUTABLE) $(OBJECTS)
