# wed - wil's editor

# include config.mk

PREFIX = /usr/local
SRC = wed.c
CC = gcc
OBJ = $(SRC:.c=.o)
LIBS = -L/usr/lib -lc -lncurses
CFLAGS = -std=c99 -pedantic

all: options wed2 pl

options:
	@echo build options:
	@echo "CC = $(CC)"
	
wed:
	@echo CC -o $@
	@$(CC) -o $@ $@.c $(LIBS) 

wed2:
	@echo CC -o $@
	@$(CC) -o $@ $@.c $(LIBS) $(CFLAGS)

pl:
	@echo CC -o $@
	@$(CC) -o $@ pl.c $(CFLAGS)

install: all
	@echo installing to $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f wed $(DESTDIR)$(PREFIX)/bin
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/wed
	
uninstall:
	@echo uninstalling from $(DESTDIR)$(PREFIX)/bin
	@rm -f $(DESTDIR)$(PREFIX)/bin/wed
	
clean:
	@echo cleaning
	@rm -f pl wed2 $(OBJ)
