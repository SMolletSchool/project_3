#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/address_book_fops.h"
//#include "abk_log.h"
#include "../include/address_book_menu.h"
#include "../include/address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */
	char choice;
	if (msg != NULL) printf(msg);
	switch (type) {
		case NONE:
			return scanf("%s");
		case NUM:
			scanf("%i", &choice);
			return choice;
		case CHAR:
			scanf("%c", choice);
			return choice;
	}

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

	system("cls");

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
         scanf("%s", &newContact.email_addresses[countEmail]); // store this name in email field for newContact
         countEmail++; // increment the countEmail variable
         goto backToMenu;
      
   }
   
   // user should be finished with data input once we reach this part...
   bookSize++; // increment the bookSize to reflect added contact
   newContact.si_no = bookSize; // assign a serial number to the new contact, using new bookSize
   address_book -> count = bookSize; // update count variable in address book
   address_book -> list[bookSize] = newContact; // finally, add new contact to the address book
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
	Status status = e_no_match; //Used to return success
	int contactFound = 0;
	switch (mode) {
		case e_first_opt: //searching for name, can just use name
			for (int i = 0; i < loop_count; i++) {
				if (strcmp(address_book->list[i].name[0], str) == 0) { //Get name from pointer
					status = e_success; //Success! set to success
					contactFound = i;
				}
			}
			break;
		case e_second_opt: //searching onwards (except serial number), needs inner loop to check each possible phone/email
			for (int i = 0; i < loop_count; i++) {
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
					if (strcmp(address_book->list[i].phone_numbers[j], str) == 0) {
						status = e_success;
						contactFound = i;
					} //Success! set to success
				}
			}
			break;
		case e_third_opt:
			for (int i = 0; i < loop_count; i++) {
				for (int j = 0; j < EMAIL_ID_COUNT; j++) {
					if (strcmp(address_book->list[i].email_addresses[j], str) == 0) {
						status = e_success;
						contactFound = i;
					} //Success! set to success;
				}
			}
			break;
		case e_fourth_opt:
		;int convert_string = atoi(str); //convert to int
			for (int i = 0; i < loop_count; i++) {
				if (address_book->list[i].si_no == convert_string) { //Int comparison
					status = e_success;
					contactFound = i;
				}
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
		render_serial(address_book->list[contactFound].si_no);
		render_text(address_book->list[contactFound].name[0]);
		render_text(address_book->list[contactFound].phone_numbers[0]);
		render_text(address_book->list[contactFound].email_addresses[0]);
		printf("\n                                          ");
		render_text(address_book->list[contactFound].phone_numbers[1]);
		render_text(address_book->list[contactFound].email_addresses[1]);
		printf("\n                                          ");
		render_text(address_book->list[contactFound].phone_numbers[2]);
		render_text(address_book->list[contactFound].email_addresses[2]);
		printf("\n                                          ");
		render_text(address_book->list[contactFound].phone_numbers[3]);
		render_text(address_book->list[contactFound].email_addresses[3]);
		printf("\n                                          ");
		render_text(address_book->list[contactFound].phone_numbers[4]);
		render_text(address_book->list[contactFound].email_addresses[4]);
		printf("\n                                          ");
		printf("============================================================================================================/n");
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

void edit_menu(void)
{
	menu_header("Search by Contact to Edit by:\n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	printf("\n");
	printf("Please select an option: ");
}

Status edit_contact(AddressBook *address_book)
{
	int temp;
    int option;
    char targetName[NAME_LEN];
	char newName[NAME_LEN];
    char targetPhone[NUMBER_LEN];
	char newPhone[NAME_LEN];
    char targetEmail[EMAIL_ID_LEN];
	char newEmail[EMAIL_ID_LEN];
	int target_si_no;
	int new_si_no;

    char input[5];
    char select = "s";
    char quit = "q";
    edit_menu();

	scanf("$d",&option);

		

	switch (option)
	{
        case 0: // back
            goto skip;
            break;
		case 1: // edit by name
			printf("Enter the Name: ");
            scanf("%s", &targetName);
            if (search(targetName,address_book,address_book->count,1,targetName,e_first_opt) == 0) 
			{
				printf("\n%s not found.", targetName);
			}
            else
            {
                menu_header("Search Result:\n");
                search(targetName,address_book,address_book->count,1,targetName,e_first_opt);
                printf("Press: [s] Select. [q] | cancel: ");
                scanf("%s",input);
                    
                if(strcmp(input,quit))
                {
                    goto skip;
                }
				if(strcmp(input,select))
				{
					printf("\nSelect a Serial Number (S.No) to Edit: ");
					scanf("%d", temp);
					printf("\nEnter new Name: ");
					scanf("%s",newName);
					strcpy(address_book->list->name, newName);
				}
            }
			break;
		case 2: // edit by phone no
			printf("Enter the Phone number: ");
            scanf("%s", &targetPhone);
            if (search(targetPhone,address_book,address_book->count,1,targetPhone,e_second_opt) == 0) 
			{
				printf("\n%s not found.", targetPhone);
			}
            else
            {
                menu_header("Search Result:\n");
                search(targetPhone,address_book,address_book->count,1,targetPhone,e_second_opt);
                printf("Press: [s] Select. [q] | cancel: ");
                scanf("%s",input);
                    
                if(strcmp(input,quit))
                {
                    goto skip;
                }
				if(strcmp(input,select))
				{
					printf("\nSelect a Serial Number (S.No) to Edit: ");
					scanf("%d", temp);
					printf("\nEnter new Phone Number: ");
					scanf("%s",newPhone);
					strcpy(address_book->list->phone_numbers, newPhone);
				}
            }
			break;	
			
		case 3: // edit by email
			printf("Enter the Email: ");
            scanf("%s", &targetEmail);
            if (search(targetEmail,address_book,address_book->count,1,targetEmail,e_third_opt) == 0) 
			{
				printf("\n%s not found.", targetEmail);
			}
            else
            {
                menu_header("Search Result:\n");
                search(targetEmail,address_book,address_book->count,1,targetEmail,e_third_opt);
                printf("Press: [s] Select. [q] | cancel: ");
                scanf("%s",input);
                    
                if(strcmp(input,quit))
                {
                    goto skip;
                }
				if(strcmp(input,select))
				{
					printf("\nEnter new Email: ");
					scanf("%s",newEmail);
					strcpy(address_book->list->email_addresses, newEmail);
				}
            }
			break;
		case 4: // edit by serial no
			printf("Enter the Serial Number: ");
            scanf("%s", &target_si_no);
            if (search(target_si_no,address_book,address_book->count,4,target_si_no,e_fourth_opt) == e_no_match) 
			{
				printf("\n%d not found.", target_si_no);
			}
            else
            {
                menu_header("Search Result:\n");
                search(target_si_no,address_book,address_book->count,4,target_si_no,e_fourth_opt);
                printf("Press: [s] Select. [q] | cancel: ");
                scanf("%s",input);
                    
                if(strcmp(input,quit))
                {
                    goto skip;
                }
				if(strcmp(input,select))
				{
					printf("\nEnter new Serial Number: ");
					scanf("%d",new_si_no);
					strcpy(address_book->list->si_no, new_si_no);
				}
            }
			break;

		default:
            printf("Invalid input. Please select 0, 1, 2, 3, or 4");
	}

	skip:
	return e_success;
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
