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
	if (*str != '\0')
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

void search_menu_display(void)
{
	menu_header("Choose search parameter:\n");

	printf("0. Exit\n");
	printf("1. Search by Name\n");
	printf("2. Search by Phone Number\n");
	printf("3. Search by Email Address\n");
	printf("4. Search by Serial Number\n");
	printf("\n");
	printf("Please select an option: ");
}

void render_serial(int number) {
	
	printf(": %i", number);

	int spaces_to_fill = 4; //Empty area would be 4 spaces
	int number_reduced = number;
	while (number_reduced != 0) {
		spaces_to_fill--; //Reduce spaces needed by each digit in the number
		number_reduced /= 10;
	}
	for (int i = 0; i < spaces_to_fill; i++)
	{
		printf(" ");
	}
}

void render_text(char* string) {
	
	printf(": %s", string);

	int spaces_to_fill = 32 - strlen(string); //Get the length of the string, and subtract how many spaces remain by that

	for (int i = 0; i < spaces_to_fill; i++)
	{
		printf(" ");
	}
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	//I have no clue what a good chunk of the fields are even for, so they'll be skipped/filled with unused variables for now.
	const ContactInfo *ContactPointer = address_book->list; //creating pointer to contact list in address book for reading
	Status status = e_no_match; //Used to return success

	switch (mode) {
		case e_first_opt: //searching for name, can just use contactpointer directly
			for (int i = 0; i < loop_count; i++) {
				if (strcmp(ContactPointer->name, str) == 0) { //Get name from pointer
					status = e_success; //Success! set to success
				}
				if (status != e_success) //If fail to find contact there,
				ContactPointer++; //Increment to next contact
			}
			break;
		case e_second_opt: //searching onwards (except serial number), needs inner loop to check each possible phone/email
			for (int i = 0; i < loop_count; i++) {
				char* phones = ContactPointer->phone_numbers;
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
					if (strcmp(phones[j], str) == 0) status = e_success; //Success! set to success
				}
			}
			break;
		case e_third_opt:
			for (int i = 0; i < loop_count; i++) {
				char* emails = ContactPointer->email_addresses;
				for (int j = 0; j < EMAIL_ID_COUNT; j++) {
					if (strcmp(emails[j], str) == 0) status = e_success; //Success! set to success
				}
			}
			break;
		case e_fourth_opt:
		;int convert_string = atoi(str); //convert to int
			for (int i = 0; i < loop_count; i++) {
				if (ContactPointer->si_no == convert_string) { //Int comparison
					status = e_success;
				}
				ContactPointer++;
			}
			break;
	}
	if (status == e_success) {
		/*
		Print contact info at pointer
		*/
		printf("============================================================================================================/n");
		printf(": S. No : Name                            : Phone No                        : Email ID                     :/n");
		printf("============================================================================================================/n");
		//print each section spaced out correctly
		render_serial(ContactPointer->si_no);
		render_text(ContactPointer->name);
		render_text(ContactPointer->phone_numbers);
		render_text(ContactPointer->email_addresses);
	}
	return status;
}

Status search_contact(AddressBook *address_book)
{
	search_menu_display();
	char* user_input;
	scanf("%c",user_input);
	printf("\nInput was %i\n", user_input);
	switch (user_input[0]) {
		case '1':
			printf("\nEnter name to search: ");
			scanf("%s", user_input);
			if (search(user_input,address_book,address_book->count,1,user_input,e_first_opt) == e_no_match) {
				printf("\n%s not found.", user_input);
			}
			break;
		case '2':
			printf("\nEnter phone number to search: ");
			scanf("%s", user_input);
			if (search(user_input,address_book,address_book->count,2,user_input,e_second_opt) == e_no_match) {
				printf("\n%s not found.", user_input);
			}
			break;
		case '3':
			printf("\nEnter email to search: ");
			scanf("%s", user_input);
			if (search(user_input,address_book,address_book->count,3,user_input,e_third_opt) == e_no_match) {
				printf("\n%s not found.", user_input);
			}
			break;
		case '4':
			printf("\nEnter serial number to search: ");
			scanf("%s", user_input);
			if (search(user_input,address_book,address_book->count,4,user_input,e_fourth_opt) == e_no_match) {
				printf("\n%s not found.", user_input);
			}
			break;
		case '0':
			break;
		default:
			printf("Invalid input!");
			break;
	}

}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
