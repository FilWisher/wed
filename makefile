# wed - wil's editor

# include config.mk

PREFIX = /usr/local
SRC = wed.c
CC = tcc
OBJ = $(SRC:.c=.o)
LIBS = -L/usr/lib -lc -lncurses

all: options wed

options:
	@echo build options:
	@echo "CC = $(CC)"
	
wed:
	@echo CC -o $@
	@$(CC) -o $@ $@.c $(LIBS) 

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
	@rm -f wed $(OBJ)
