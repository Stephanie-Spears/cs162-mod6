/* The header file for class EntryList.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/
#ifndef ENTRY_LIST
#define ENTRY_LIST

#include "AddressEntry.h"

const int ADDRESS_BOOK_CAPACITY = 100;
const int NAME_COL_WIDTH = 30;
const int EMAIL_COL_WIDTH = 40;

class EntryList
{
public: 
	//constructors
	EntryList();
	EntryList(int initCapacity, const char fileName[]);

	//destructor
	~EntryList();

	//accessor functions
	bool get(int index, AddressEntry& anEntry) const;
	bool searchEntry(const char name[], AddressEntry& match) const;
	int getSize() const;
	void printAll() const;
	void saveAddressBook(const char fileName[]) const;

	//mutator functions
	void addEntry(const AddressEntry& anEntry);
	void loadAddressBook(const char fileName[]);
	
	
private:
	AddressEntry *	list;
	int				size;
	int				capacity;

	void expandList();
};

#endif