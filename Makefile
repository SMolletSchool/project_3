CC=gcc

all: program

program: src\address_book_fops.c src\address_book_menu.c src\main.c
	$(CC) -o addressbook src\address_book_fops.c src\address_book_menu.c src\main.c

clean:
	del *.exe *.o