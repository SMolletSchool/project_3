CC=gcc

all: program

program: address_book_fops.c address_book_menu.c main.c
	$(CC) -o addressbook address_book_fops.c address_book_menu.c main.c

clean:
	del *.exe *.o