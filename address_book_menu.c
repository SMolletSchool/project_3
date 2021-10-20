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
				add_contacts(address_book);
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
	ContactInfo newContact; // creates a new contact to be added to the address book
   int choice; // variable to save user choice
   int countPhone = 1, countEmail = 1; // stores how many different phone numbers/emails user will input. used when listing fields
   backToMenu: ; // using goto to jump back to the add menu while retaining new data
   menu_header("Add Contact:"); // shows header
   printf("0.  Back\n1. Name:    %s\n2. Phone No %d:     %s\n3.  Email ID %d:    %s\n", newContact.name, countPhone, newContact.phone_numbers, countEmail, newContact.email_addresses); // show all available options
   printf("Please select an option: "); // prompt user to choose an option
   scanf("%d", &choice); // save option into variable choice
   int bookSize = address_book -> count; // create var bookSize to store size of address book
   
   switch(choice) {
      case 0: // user will go back to main menu
         break; // all done with data input. exit this switch case, then go on to saving new contact.
      case 1: // user wants to add a name
         printf("\nEnter the name: "); // prompt user for name
         scanf("%s", &newContact.name[0]); // store this name in name field for newContact
         goto backToMenu; // jump back to add menu
      case 2: // user wants to add phone number
         printf("\nEnter phone number %d: ", countPhone); // prompt user for name
         scanf("%s", &newContact.phone_numbers[countPhone]); // store this name in phone field for newContact
         countPhone++; // increment countPhone variable
         goto backToMenu;
      case 3: // user wants to add email
         printf("\nEnter email %d: ", countEmail); // prompt user for name
         scanf("%s", &newContact.email.addresses[countEmail]); // store this name in email field for newContact
         countEmail++; // increment the countEmail variable
         goto backToMenu;
      
   }
   
   // user should be finished with data input once we reach this part...
   bookSize++; // increment the bookSize to reflect added contact
   newContact.si_no = bookSize; // assign a serial number to the new contact, using new bookSize
   address_book -> count = bookSize; // update count variable in address book
   address_book -> list[bookSize] = newContact; // finally, add new contact to the address book
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
	/* Add the functionality for delete contacts here */
}
