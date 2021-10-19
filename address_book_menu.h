#ifndef ABK_MENUS_H
#define ABK_MENUS_H

#include "address_book.h"

#define	NONE							0
#define	NUM								1
#define	CHAR							2
#define WINDOW_SIZE						5

void menu_header(const char *str);
void main_menu(void);

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode);

#endif
