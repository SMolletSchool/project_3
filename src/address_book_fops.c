#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "../include/address_book.h"

int read_items(AddressBook *address_book)
{ //Function to read the file and populate the contact info
	address_book->fp = fopen(DEFAULT_FILE, "r"); //open for reading

	//First count the lines in the file
	address_book->count = 0;
	for (char c = getc(address_book->fp); c != EOF; c = getc(address_book->fp)) { //Repeats until we reach the end of the file
		if (c == '\n') {
			address_book->count += 1; //increment count for every new line
			
			printf("counter incremented\n");	
		} 
		
	}
	
	//Then read the lines to populate the address book's contact list
	fseek(address_book->fp,0,SEEK_SET); //reset file pointer position
	char buf[32]; //make a line buffer

	memset(buf,0,sizeof(buf-1)); //empty the buffer here to clean it
	int section = 0; //make a section variable
	const int contactSize = sizeof(ContactInfo); //use this for doing malloc

	printf("contact size initialized to %i\n", contactSize);
	printf("count is equal to %i\n", address_book->count);
	printf("%i bytes should be allocated\n", contactSize*(address_book->count));

	address_book->list = malloc((address_book->count)*contactSize); //Allocate data for the contacts

	printf("%i bytes allocated\n", (address_book->count)*contactSize);
	char c[1];
	for (int i = 0; i < address_book->count; i++) { //For every contact
		for (c[0] = getc(address_book->fp); c[0] != NEXT_ENTRY; c[0] = getc(address_book->fp)) { //Repeat until we reach the newline
			
			printf("current char: %c\n", c[0]);
			
			if (c[0] == FIELD_DELIMITER) { //found a comma, time to populate this section
				
				printf("attempting to populate contact %i\n", i);
				
				//If the buffer isn't empty
				switch (section) {
					case 0: //Serial number
						
						printf("attempting to write %s to address %p\n", buf, address_book->list[i].si_no);
						
						address_book->list[i].si_no = atoi(buf);
						
						printf("serial number written as %i\n", address_book->list[i].si_no);
						
						break;
					case 1: //Name
						
						printf("attempting to write %s to address %p\n", buf, address_book->list[i].name[0]);
						
						strcpy(address_book->list[i].name[0], buf);
						
						printf("name written as %s\n", address_book->list[i].name[0]);
						
						break;
					case 2: //Phone number 0
						
						printf("attempting to write %s to address %p\n", buf, &(address_book->list->phone_numbers[0]));
						
						strcpy(address_book->list[i].phone_numbers[0], buf);
						
						printf("phone 0 written as %s\n", address_book->list[i].phone_numbers[0]);
						
						break;
					case 3: //Phone number 1
						
						printf("attempting to write %s to address %p\n", buf, address_book->list->phone_numbers[1]);
						
						strcpy(address_book->list[i].phone_numbers[1], buf);
						
						printf("phone 1 written as %s\n", address_book->list[i].phone_numbers[1]);
						
						break;
					case 4: //Phone number 2
						strcpy(address_book->list[i].phone_numbers[2], buf);
						
						printf("phone 2 written as %s\n", address_book->list[i].phone_numbers[2]);
							break;
					case 5: //Phone number 3
						strcpy(address_book->list[i].phone_numbers[3], buf);
						
						printf("phone 3 written as %s\n", address_book->list[i].phone_numbers[3]);
						
						break;
					case 6: //Phone number 4
						strcpy(address_book->list[i].phone_numbers[4], buf);
						
						printf("phone 4 written as %s\n", address_book->list[i].phone_numbers[4]);
						break;
					case 7: //Email 0
						strcpy(address_book->list[i].email_addresses[0], buf);
						
						printf("email 0 written as %s\n", address_book->list[i].email_addresses[0]);
						
						break;
					case 8: //Email 1
						strcpy(address_book->list[i].email_addresses[1], buf);
						
						printf("email 1 written as %s\n", address_book->list[i].email_addresses[1]);
						
						break;
					case 9: //Email 2
						strcpy(address_book->list[i].email_addresses[2], buf);
						
						printf("email 2 written as %s\n", address_book->list[i].email_addresses[2]);
						
						break;
					case 10: //Email 3 AND 4
						strcpy(address_book->list[i].email_addresses[3], buf);
						
						printf("email 3 written as %s\n", address_book->list[i].email_addresses[3]);

						break;
					case 11: //Email 4
						strcpy(address_book->list[i].email_addresses[4], buf);
						
						printf("email 4 written as %s\n", address_book->list[i].email_addresses[4]);
						
						break;
				}
				memset(buf,0,sizeof(buf-1)); //empty the buffer for the next word
				printf("buffer emptied\n");
				section++;
				printf("section incremented\n");
			}
			else {
				
				printf("attempting to concatenate to buffer\n", c);
				
				strncat(buf,c,1);

				printf("char concatenated, buffer is now %s\n", buf);
			}
		}
		section = 0;
		
		printf("section reset\n");
	}
	fclose(address_book->fp);
	return 1;
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
		printf("File exists.\n");

		int test_read = read_items(address_book);
		
		if (test_read == -1) {
			return e_fail;
		}

	}
	else
	{
		/* Create a file for adding entries */
		printf("File doesn't exist, making file.\n");

		address_book->fp = fopen(DEFAULT_FILE, "w"); //open for writing, to create the file
		fclose(address_book->fp); //then close the file, we don't need it yet
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
	char* pause = "a";
	int chars_written = 0;
	char* into_file;
	for (int items = 0; items < address_book->count; items) { //repeat for each contact

		printf("Attempting to write to file, contact %i\n", items);

		
		chars_written = fprintf(address_book->fp, "%d,", address_book->list[items].si_no);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].name[0]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);

		strcpy(into_file,address_book->list[items].phone_numbers[0]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);

		strcpy(into_file,address_book->list[items].phone_numbers[1]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);

		strcpy(into_file,address_book->list[items].phone_numbers[2]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].phone_numbers[3]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].phone_numbers[4]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].email_addresses[0]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].email_addresses[1]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].email_addresses[2]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].email_addresses[3]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		
		strcpy(into_file,address_book->list[items].email_addresses[4]);
		chars_written = fprintf(address_book->fp, "%s,", into_file);
		printf("Wrote %d characters to %d\n", chars_written, address_book->fp);
		

		printf("wrote %d, %s, %s, %s, %s, %s, %s, %s, %s, %s", address_book->list[items].si_no,address_book->list[items].name[0],address_book->list[items].phone_numbers[1], address_book->list[items].phone_numbers[2], address_book->list[items].phone_numbers[3], address_book->list[items].phone_numbers[4], address_book->list[items].email_addresses[0], address_book->list[items].email_addresses[1], address_book->list[items].email_addresses[2], address_book->list[items].email_addresses[3], address_book->list[items].email_addresses[4]);
		printf("Paused, press any combination of letters and then enter to unpause. \n");
		scanf("%s", pause);
	}
	fclose(address_book->fp);

	return e_success;
}
