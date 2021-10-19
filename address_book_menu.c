#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	int choice; //user input choice
	menu_header("Delete Contact"); //calls menu header
	printf("0.  Back\n1.  Name\n2.  Phone #\n3.  Email ID\n4.Serial #\n\n"); //available options are printed
	printf("Please select an option"); //has user select an option
	scanf("$d",&choice); //takes user's input
	int sizeAddressBook = address_book -> count;
	char targetName[NAME_LEN];
	char targetPhone[NUMBER_LEN];
	char targetEmail[EMAIL_ID_LEN];
	int targetID; 
	int phoneNumber = 0; 
	int email = 0; 
	int loop = 0; 
	const AddressBook *endPtr = address_book + sizeAddressBook; //added pointer to point to the beginning 
	int sizeOfArrayPhone;  
	int sizeOfArrayEmail; 
	switch(choice){
		case '0' :
			menu(address_book); //this calls menu
		case '1' :
			printf("\nEnter the Name: "); //asks for the name
			scanf("%s", &targetName); // input the name
			for(address_book < endPtr; address_book++;){ //loops each element of addressbook
				if(strcmp(*address_book -> list -> name, targetName) == 0){
					for(; address_book < endPtr-1; address_book++){
						address_book = address_book + 1; 
					}
					break; 
				}
				delete_contact(address_book);
			}
		case '2' : 
			printf("\nEnter the Phone Number: "); //asks for phone #
			scanf("%s", &targetPhone); //input phone #
			sizeOfArrayPhone = sizeof(address_book -> list -> phone_numbers)/ sizeof(address_book -> list -> phone_numbers[0]);
			for(; address_book < endPtr; address_book++){ //loops each element of addressbook 
				while(loop < sizeOfArrayPhone){
					if(strcmp(address_book -> list -> phone_numbers[loop], targetPhone) == 0){ // if element = to target phone #
						for(; address_book < endPtr-1; address_book++){
							address_book = address_book + 1;
						}
					break; 
					}
					loop++; 
				}
				delete_contact(address_book);
			}
		case '3' : 
			printf("\nEnter the Email: "); //enter email
			scanf("%s", &targetEmail); //user input
			sizeOfArrayPhone = sizeof(address_book -> list -> email_addresses)/ sizeof(address_book -> list -> email_addresses[0]);
			for(; address_book < endPtr; address_book++){ //loop through all elements
				while(loop < sizeOfArrayEmail){
					if(strcmp(address_book -> list -> email_addresses[loop], targetEmail) == 0){ //if target email found, continue
						for(; address_book < endPtr-1; address_book++){
							address_book = address_book+1;
						}	
					break; 
					}
					loop++; 
				}
				delete_contact(address_book);
			}
		case '4' :
			printf("\nEnter the ID: "); //enter ID
			scanf("%d", &targetID); //user input
			for(; address_book < endPtr; address_book++){
				if(address_book -> list -> si_no = targetID){
					for(; address_book < endPtr-1; address_book++){
						address_book = address_book+1; 
					}
					break; 
				delete_contact(address_book);
				}
			}
	}
		
	
}

