# wed

CC = gcc
CFLAGS = -pedantic -Wall -std=c99

TARGET = wed
SOURCE = $(filter-out main.c, $(wildcard *.c))
OBJECTS = $(SOURCE:.c=.o)

##all: $(OBJECTS) $(TARGET) 

wed:
	$(CC) $(CFLAGS) main.c file.c piece.c text.c -o wed

#$(TARGET): $(OBJECTS) main.c
#	$(CC) $(CFLAGS) main.c $(OBJECTS) -o $(TARGET)
#
#$(OBJECTS): $(SOURCE)
#	$(CC) -c $(@:.o=.c) -o $@
#	
#clean:
#	@-rm -f $(OBJECTS) $(TARGET)
