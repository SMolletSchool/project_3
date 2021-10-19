#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "address_book_log.h"
#include "address_book_menu.h"
#include "address_book_fops.h"
#include "address_book.h"

// list contacts

void list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{

	if (address_book == NULL ) // nothing to display
	{
		printf("Address Book is empty\n");
		return ;
	}
	printf("  NAME  ||  NUMBER  ||  EMAIL  \n"); // header for contacts
	
	size_t i = 0;
	for (; i < address_book->size; ++i) // run through contacts and print out info
	{
		printf("  %s  ||  %s  ||  %s  \n", 
			address_book->data[i].name,
			address_book->data[i].number,
			address_book->data[i].email);
	}
	return ;
}
