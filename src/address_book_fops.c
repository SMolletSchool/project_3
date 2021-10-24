#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "../include/address_book.h"

void read_items(AddressBook *address_book)
{ //Function to read the file and populate the contact info
	//First count the lines in the file
	address_book->count = 0;
	for (char c = getc(address_book->fp); c != EOF; c = getc(address_book->fp)) { //Repeats until we reach the end of the file
		if (c == '\n') {
			address_book->count++; //increment count for every new line
			//printf("counter incremented\n");	
		} 
		
	}

	
	//Then read the lines to populate the address book's contact list
	fseek(address_book->fp,0,SEEK_SET); //reset file pointer position
	char buf[32]; //make a line buffer

	memset(buf,0,sizeof(buf-1)); //empty the buffer here to clean it
	int buf_index = 0; //create an index variable to point at each character in buf
	
	int section = -1; //make a section variable
	//ContactInfo *contactPointer = address_book->list; //Make a pointer for writing to the list?

	int contactSize = sizeof(ContactInfo);
	printf("contact size initialized to %i\n", contactSize);
	printf("count is equal to %i\n", address_book->count);
	printf("%i bytes should be allocated\n", contactSize*(address_book->count));
	address_book->list = malloc((address_book->count)*contactSize); //Allocate data for the contacts
	printf("%i bytes allocated\n", (address_book->count)*contactSize);
	for (int i = 0; i < address_book->count; i++) { //For every contact
		for (char c = getc(address_book->fp); c != NEXT_ENTRY; c = getc(address_book->fp)) { //Repeat until we reach the newline
			printf("current char: %c\n", c);
			if (c == FIELD_DELIMITER) { //found a comma, time to populate this section
				printf("attempting to populate contact %i\n", i);
				if (*buf != "\0") {//If the buffer isn't empty
					switch (section) {
						case -1: //Serial number
							printf("attempting to write to address %i\n", address_book->list[i].si_no);
							address_book->list[i].si_no = atoi(buf);
							printf("serial number written as %i\n", address_book->list[i].si_no);
							break;
						case 0: //Name
							printf("attempting to write to address %i\n", address_book->list[i].name);
							strcpy(address_book->list[i].name, buf);
							printf("name written as %s\n", address_book->list[i].name);
							break;
						case 1: //Phone number 1
							printf("attempting to write to address %i\n", address_book->list->phone_numbers[0]);
							strcpy(address_book->list[i].phone_numbers[0], buf);
							printf("phone 0 written as %s\n", address_book->list[i].phone_numbers[0]);
							break;
						case 2: //Phone number 2
							printf("attempting to write to address %i\n", address_book->list->phone_numbers[1]);
							strcpy(address_book->list[i].phone_numbers[1], buf);
							printf("phone 1 written as %s\n", address_book->list[i].phone_numbers[1]);
							break;
						case 3: //Phone number 3
							strcpy(address_book->list[i].phone_numbers[2], buf);
							break;
						case 4: //Phone number 4
							strcpy(address_book->list[i].phone_numbers[3], buf);
							//printf("phone 3 written\n");
							break;
						case 5: //Phone number 5
							strcpy(address_book->list[i].phone_numbers[4], buf);
							//printf("phone 4 written\n");
							break;
						case 6: //Email 1
							strcpy(address_book->list[i].email_addresses[0], buf);
							//printf("email 0 written\n");
							break;
						case 7: //Email 2
							strcpy(address_book->list[i].email_addresses[1], buf);
							//printf("email 1 written\n");
							break;
						case 8: //Email 3
							strcpy(address_book->list[i].email_addresses[2], buf);
							//printf("email 2 written\n");
							break;
						case 9: //Email 4
							strcpy(address_book->list[i].email_addresses[3], buf);
							//printf("email 3 written\n");
							break;
						case 10: //Email 5
							strcpy(address_book->list[i].email_addresses[4], buf);
							//printf("email 4 written\n");
							break;
					}
					memset(buf,0,sizeof(buf-1)); //empty the buffer for the next word
					printf("buffer emptied\n");
				}
				section++;
				printf("section incremented\n");
			}
			else {
				printf("attempting to concatenate %c to buffer\n", c);
				buf[buf_index] = (char) c; //concatenate character onto buffer
				buf_index++; //increment index for next char
				printf("char concatenated\n");
			}
		}
		section = -1;
		printf("section reset\n");
		buf_index = 0;
	}
}

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */

	ret = access(DEFAULT_FILE,F_OK);

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		address_book->fp = fopen(DEFAULT_FILE, "r"); //open for reading
		read_items(address_book);
		fclose(address_book->fp);

	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w+"); //open for reading and writing, while creating the file
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */
	printf("Attempting to open %s\n", DEFAULT_FILE);
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		printf("Failed to open.\n");
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */
	printf("Opened successfully.\n");
	for (int items = 0; items < address_book->count; items) { //repeat for each contact
		//Instead of separating the writing into multiple statements, just use one really long write
		printf("Attemping to write to file, contact %i\n", items);
		fprintf(address_book->fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", address_book->list[items].si_no,address_book->list[items].name[0],address_book->list[items].phone_numbers[0],address_book->list[items].phone_numbers[1],address_book->list[items].phone_numbers[2],address_book->list[items].phone_numbers[3],address_book->list[items].phone_numbers[4],address_book->list[items].email_addresses[0],address_book->list[items].email_addresses[1],address_book->list[items].email_addresses[2],address_book->list[items].email_addresses[3],address_book->list[items].email_addresses[4]);
		printf("Wrote %d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",address_book->list[items].si_no,address_book->list[items].name[0],address_book->list[items].phone_numbers[0],address_book->list[items].phone_numbers[1],address_book->list[items].phone_numbers[2],address_book->list[items].phone_numbers[3],address_book->list[items].phone_numbers[4],address_book->list[items].email_addresses[0],address_book->list[items].email_addresses[1],address_book->list[items].email_addresses[2],address_book->list[items].email_addresses[3],address_book->list[items].email_addresses[4]);
	}
	fclose(address_book->fp);

	return e_success;
}
