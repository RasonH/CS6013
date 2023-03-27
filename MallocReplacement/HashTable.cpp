#include <cstdlib>
#include <cstdio>
#include <sys/mman.h>
#include <unistd.h>
#include "HashTable.h"


HashTable::HashTable(){
	//getpagesize(): get memory page size:
	capacity = getpagesize() / sizeof(TableEntry);
	// table
	table = (TableEntry*) mmap(NULL, capacity * sizeof(TableEntry), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); // 0 means file descriptor read, 0 = offset

	if(table == MAP_FAILED){
		perror("MMAP Allocation failed");
		exit(1);
	}
	size = 0;
}

// put a pointer and memory size
void HashTable::insert(void* pointer, size_t memorySize) {
	// check if we need to grow the table
	double loadFactor = (double) size / capacity;
	if(loadFactor > 1/2){ // if 1/2 size grow the table
		grow();

	}
	size_t key = hash(pointer);

	while(table[key].flag == 1) {

		key++;
		if(key >= capacity){
			key-= capacity; // to do the wrap around
		}
	}

	table[key].pointer = pointer;
	table[key].size = memorySize;
	table[key].flag = 1;
	size++; // to implement the insert

}


void HashTable::remove(void* pointer){
	size_t key = hash(pointer);

	while(table[key].pointer != pointer && table[key].flag == 1){ // need to check until found the pointer:
		key++;
		if(key >= capacity){
			key -= capacity;
		}
	}
	if (table[key].flag == 1) {
		table[key].flag = -1;
		size--; // decrease the size
	}

}

//to access the value directly by using the pointer:
size_t HashTable::get(void* pointer){

	size_t key = hash(pointer);

	while(table[key].pointer != pointer && table[key].flag == 1){ // need to check until found the pointer:
		key++;
		if(key >= capacity){
			key -= capacity;
		}
	}
	if(table[key].flag == 1){
		return table[key].size;
	}
	return -1;

}

size_t HashTable::getSize(){

	return size;
}

// destructor
HashTable::~HashTable(){

}


// we are hashing a pointer
int HashTable::hash(void* pointer){
	int hashValue = ((size_t)pointer >> 12) % capacity;
	return hashValue;
}


// if size is equal to the capacity, then increase the capacity by double
void HashTable::grow(){
	size_t newCapacity = capacity * 2;
	TableEntry* newTable = (TableEntry*) mmap(NULL, newCapacity * sizeof(TableEntry), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(newTable == MAP_FAILED){
		perror("MMAP Allocation failed.");
		exit(1);
	}

	TableEntry* oldTable = table;
	size_t oldCapacity = capacity;
	this->capacity = newCapacity;
	this->table = newTable;
	this->size = 0;
	for(int i =0; i < oldCapacity; i++) {
		if(oldTable[i].flag == 1){
			insert(oldTable[i].pointer, oldTable[i].size);
		}
	}
}