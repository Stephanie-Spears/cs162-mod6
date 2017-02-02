/* This program demonstrates how to use pointers and how to allocate memory dynamically.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/
#include "InputTools.h"
#include <iostream>  
using namespace std; 

const int CAPACITY = 3;

void displayArray(int intList[], int size);

//define a new data type AddressEntry
const int MAX_CHAR = 101;

struct AddressEntry
{
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];
};

int main()
{
	int				intVal = 10;
	int *			intPtr;

	//introduce & and *
	intPtr = &intVal; 
	cout << endl << "intPtr = " << intPtr << endl;
	cout << endl << "&intVal = " << &intVal << endl;
	cout << endl << "*intPtr = " << *intPtr << endl;

	*intPtr = 20;
	cout << endl << "intVal = " << intVal << endl;

	//introduce new and delete
	intPtr = new int;
	*intPtr = 30;
	cout << endl << "intPtr = " << intPtr << endl 
		<< "*intPtr = " << *intPtr << endl;
	delete intPtr;

	//static array where array name is a const pointer. It can not point to anywhere else.
	//the size of the array has to be determined at compile time
	int				intArray[CAPACITY];
	int	*			intArrayDynamic;
	int				capacity;
	int				index;

	for(index=0; index<CAPACITY; index++)
		intArray[index] = index+1;
	cout << endl << "The content of the static array: " << endl;
	displayArray(intArray, CAPACITY);

	//dynamic array where array name is a pointer. 
	//the size of the array can be determined at run time
	capacity = readInt("Please enter the preferred size of the array: ");
	intArrayDynamic = new int[capacity];
	for(index=0; index<capacity; index++)
		intArrayDynamic[index] = index + 1;
	cout << endl << "The content of the dynamic array: " << endl;
	displayArray(intArrayDynamic, capacity);

	//intArray or intArrayDynamic (array names) is just a pointer to the first element of the array
	cout << endl << "*intArray: " << *intArray << endl;

	//pointer arithmatic *(intArray+2) is equivalent to intArray[2]
	cout << endl << "*(intArray+2): " << *(intArray+2) << endl;	

	delete [] intArrayDynamic;

	//different pointer type
	AddressEntry *	addrPtr;
	addrPtr = new AddressEntry;

	//first use * to dereference addrPtr to get to the object, then use . to access field
	strcpy((*addrPtr).name, "Sarah Smith");		

	//here is a short cut operator '->' which means the same as above, first *, then .
	strcpy(addrPtr->email, "sarah_smith@hotmail.com");

	//release memory
	//Note: it doesn't delete the pointer, it deletes the memory the pointer points to
	delete addrPtr;

	//allocate an array of AddressEntry
	addrPtr = new AddressEntry[CAPACITY];
	
	//do some work with the array

	//release the array
	delete [] addrPtr;

	return 0;
}

/* This function displays the integer list passed in.
   in: intList and size
*/
void displayArray(int intList[], int size)
{
	int index;
	for(index=0; index<size; index++)
		cout << index << "->" << intList[index] << endl;
}