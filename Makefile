CC=gcc


ifeq ($(OS),Windows_NT)
	DIRSEP=\\
	DELETE=del
else
	DIRSEP=/
	DELETE=rm
endif

all: program

program: src$(DIRSEP)address_book_fops.c src$(DIRSEP)address_book_menu.c src$(DIRSEP)main.c
	$(CC) -o bin$(DIRSEP)addressbook src$(DIRSEP)address_book_fops.c src$(DIRSEP)address_book_menu.c src$(DIRSEP)main.c

clean:
	$(DELETE) bin$(DIRSEP)*.exe *.exe *.o