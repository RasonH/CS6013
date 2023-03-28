#pragma include once
#include <iostream>
#include <cstddef>
#include <sys/mman.h>

#define INITIAL_CAPACITY 11

class MyHashNode {
 public:
	void* pointer_;
	size_t size_;
	bool has_deleted_; // to indicate if the memory is free or not

	// constructors
	MyHashNode(): pointer_(nullptr), size_(0), has_deleted_(false) {};
	~MyHashNode() = default;
	MyHashNode(void* pointer, size_t size, bool hasDeleted){
		this->pointer_ = pointer;
		this->size_ = size;
		this->has_deleted_ = hasDeleted;
	}
};

class MyHashTable {
 public:
	size_t table_size_;
	size_t capacity_;
	MyHashNode **table_; // where actually tracks the array of pointers

	// constructors
	MyHashTable();
	~MyHashTable();

	// methods
	void grow();
	void insert(MyHashNode* node);
	void remove(MyHashNode* node);
	size_t findAndRemove(void* ptr);
	uint64_t hash(void* ptr);
	void print();
};
