#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "MyMalloc.h"


//Constructor
MyMalloc::MyMalloc(){
	pageSize = getpagesize();

}
//Destructor
MyMalloc::~MyMalloc(){

}

//hash table insert, delete, grow
HashTable MyMalloc::getTable(){

	return table;
}


void* MyMalloc::allocate(size_t bytesToAllocate){
	void* pointer =  mmap(NULL, bytesToAllocate, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0); // 0 means file descriptor read, 0 = offset

	if(pointer == MAP_FAILED){
//        report and error:
		perror("MMAP Allocation fail.");
		exit(1);
	}
	table.insert(pointer, bytesToAllocate);

	return pointer;
}

void MyMalloc::deallocate(void* ptr){
	if(munmap(ptr, table.get(ptr)) != 0){
		// report and error:
//        perror("munmap De-allocation fail.");

	}

	table.remove(ptr); // remove pointer from the table
}
