#ifndef MALLOC_MYMALLOC_H
#define MALLOC_MYMALLOC_H

#include <stdio.h>
#include "HashTable.h"

class MyMalloc {
 public:

	void* allocate(size_t bytesToAllocate);

	void deallocate(void* ptr);

//    Constructor/Destructor

	//Constructor
	MyMalloc();

	//Destructor
	~MyMalloc();

	//hash table insert, delete, grow
	HashTable getTable();

 private:
	size_t pageSize; // to keep track page size
	HashTable table; // to keep track table

};


#endif //MALLOC_MYMALLOC_H