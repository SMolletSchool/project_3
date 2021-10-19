#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

// save and exit

Status save_file(AddressBook *address_book) //
{
	/*
	 * Write contacts back to file.
s	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add logic to save the file make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}

Status exit_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to close the file
		 * Do error handling
		 */ 
	}
	else
	{
		/* Create a file for adding entries */
	}

	return e_success;
}