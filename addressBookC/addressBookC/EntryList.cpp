/* The implementation file for class EntryList.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

#include "EntryList.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/* Default constructor. It initializes the list to be empty.
*/
EntryList::EntryList()
{
	capacity = ADDRESS_BOOK_CAPACITY;
	list = new AddressEntry[capacity];
	size = 0;
}

/* A constructor that initializes the list with data on the passed in file.
   in: fileName
*/
EntryList::EntryList(int initCapacity, const char fileName[])
{
	capacity = initCapacity;
	list = new AddressEntry[capacity];
	size = 0;
	loadAddressBook(fileName);
}

/* Destructor. It releases the memory allocated for the array.
*/
EntryList::~EntryList()
{
	if(list != NULL)
		delete [] list;
}

/* This function reads the entries from the file and adds them to the list.
   in: fileName
*/
void EntryList::loadAddressBook(const char fileName[])
{
	ifstream		in;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];
	AddressEntry	anEntry;

	in.open (fileName);
	if(!in)
	{
		in.clear();
		cerr << endl << "Fail to open " << fileName << " for input!" << endl << endl;
		exit(1);
	}

	in.get(name, MAX_CHAR, ';');
	while (!in.eof())
	{
		in.get();							//remove field seperator ';'			
		in.get(email, MAX_CHAR, '\n');
		in.ignore(100, '\n');				//remove record seperator '\n'

		anEntry.setName(name);
		anEntry.setEmail(email);

		addEntry(anEntry);

		in.get(name, MAX_CHAR, ';');		//start the next record
	}
	in.close();
}

/* This function returns the size of the list.
   return: size
*/
int EntryList::getSize() const
{
	return size;
}

/* This function returns the AddressEntry object at the specified position through parameter
   in: index
   out: anEntry
   return: true if the entry exist, false if illegal index is passed in
*/
bool EntryList::get(int index, AddressEntry &anEntry) const
{
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	if(index<0 || index>=size)
		return false;

	list[index].getEmail (email);
	list[index].getName (name);
	anEntry.setEmail (email);
	anEntry.setName(name);	
	return true;
}

/* This function searches the list for an entry with passed in name. 
   in: name
   out: match
   return: true if a match is found and match will be returned through parameter.
           false if a match can not be found and match contains garbage.
*/
bool EntryList::searchEntry(const char name[], AddressEntry &match) const
{
	int		index;
	char	currentName[MAX_CHAR];
	char	currentEmail[MAX_CHAR];

	for(index=0; index<size; index++)
	{
		list[index].getName (currentName);
		list[index].getEmail(currentEmail);
		if(strcmp(name, currentName) == 0)
		{
			match.setName(currentName);
			match.setEmail(currentEmail);
			break;
		}
	}
	if (index == size)
		return false;
	else
		return true;
}

/* This function prints all the entries to the standard output.
*/
void EntryList::printAll() const
{
	int		index;
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	cout << setw(NAME_COL_WIDTH) << "Name" << setw(EMAIL_COL_WIDTH) << "Email" << endl;
	for(index=0; index<size; index++)
	{
		list[index].getName(name);
		list[index].getEmail (email);
		cout << setw(NAME_COL_WIDTH) << name << setw(EMAIL_COL_WIDTH) << email << endl;
	}
}

/* This function saves the list to the external file.
   in: fileName
*/
void EntryList::saveAddressBook(const char fileName[]) const
{
	ofstream		out;
	int				index;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];

	out.open (fileName);
	if(!out)
	{
		out.clear();
		cerr << endl << "Fail to open " << fileName << " for output!" << endl << endl;
		exit(1);
	}

	for(index=0; index<size; index++)
	{
		list[index].getName(name);
		list[index].getEmail(email);
		out << name << ';' << email << endl;
	}

	out.close();
}

/* This function adds a passed in entry to the end of the list.
   in: anEntry
*/
void EntryList::addEntry(const AddressEntry &anEntry)
{
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	if(size == capacity)
	{
		expandList();
	}
	anEntry.getName(name);
	anEntry.getEmail(email);
	list[size].setName(name);
	list[size].setEmail(email);

	size++;
}

/* This function creats a new array that is twice as big as the current one. It copies the 
   AddressEntry objects over to this new array.
*/
void EntryList::expandList()
{
	AddressEntry *	tempList;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];
	int				index;

	//create new array
	capacity *= 2;
	tempList = new AddressEntry[capacity];

	//copy over the contents
	for(index=0; index<size; index++)
	{
		list[index].getName(name);
		list[index].getEmail(email);
		tempList[index].setName(name);
		tempList[index].setEmail(email);
	}

	//release the memory from the old array
	delete [] list;

	//make list point to the new array
	list = tempList;
	tempList = NULL;
}