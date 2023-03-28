#include "MyHashTable.h"

MyHashTable::MyHashTable() : capacity_(INITIAL_CAPACITY), table_size_(0) {
	table_ = static_cast<MyHashNode**>(mmap(nullptr, capacity_ * sizeof(MyHashNode *),
											PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
	if(table_ == MAP_FAILED){
		std::cerr << "mmap failed - MyHashTable()" << std::endl;
		exit(1);
	}
	for(size_t i = 0; i < capacity_; i++){
		table_[i] = nullptr;
	}
}

MyHashTable::~MyHashTable() {
	if (munmap(table_, capacity_ * sizeof(MyHashNode *)) == -1){
		std::cerr << "munmap failed - ~MyHashTable()" << std::endl;
	} else {
		std::cout << "Deconstruct activated - ~MyHashTable()" << std::endl;
		table_ = nullptr;
		capacity_ = 0;
		table_size_ = 0;
	}
}

void MyHashTable::grow(){
	size_t newCapacity = capacity_ * 2; // TODO: find next prime will be better to solve hash conflict
	MyHashNode **newTable = static_cast<MyHashNode**>(mmap(nullptr, newCapacity * sizeof(MyHashNode*),
															PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
	);

	if (newTable == MAP_FAILED) {
		std::cerr << "mmap failed - grow()" << std::endl;
		exit(1);
	}

	// Copy all nodes from old table to new table
	for (size_t i = 0; i < capacity_; i++) {
		if ((table_[i] != nullptr) && (!table_[i]->has_deleted_)) {
			size_t newIndex = hash(table_[i]->pointer_) % newCapacity;
			while (newTable[newIndex] != nullptr) { // linear probing
				newIndex = (newIndex + 1) % newCapacity;
			}
			newTable[newIndex] = table_[i];
		}
	}

	// Swap old and new tables - after swap actually newTable is the 'old table', this becomes new
	std::swap(table_, newTable);
	// Deallocate old table
	munmap(newTable, capacity_ * sizeof(MyHashNode *));
	capacity_ = newCapacity;
}

void MyHashTable::insert(MyHashNode *node) {
	if (table_size_ >= capacity_ / 2) {
		grow();
	}
	size_t index = hash(node->pointer_) % capacity_;
	while (table_[index] != nullptr && !table_[index]->has_deleted_) {
		index = (index + 1) % capacity_;
	}
	table_[index] = node;
	table_size_++;
}

void MyHashTable::remove(MyHashNode *node) {
	size_t index = hash(node->pointer_) % capacity_;
	while (table_[index] != nullptr) { // do not set table_[index] to nullptr to avoid trouble caused by deletion order
		if (table_[index] == node) {
			table_[index]->has_deleted_ = true;
			table_size_--;
			return;
		}
		index = (index + 1) % capacity_;
	}
}

size_t MyHashTable::findAndRemove(void* ptr){
	size_t index = hash(ptr) % capacity_;
	while (table_[index] != nullptr && index < capacity_) {
		if (table_[index]->pointer_ == ptr && !table_[index]->has_deleted_) {
			size_t size = table_[index]->size_;
			remove(table_[index]);
			return size;
		}
		index = (index + 1) % capacity_;
	}
	return -1; // node not found
}

// Using a simple hash function for hashing memory addresses
uint64_t MyHashTable::hash(void* ptr){
//	std::size_t hash = 5381;
//	std::uint8_t* bytes = reinterpret_cast<std::uint8_t*>(ptr);
//	for (std::size_t i = 0; i < sizeof(void*); i++) {
//		hash = ((hash << 5) + hash) + bytes[i];
//	}
	uint64_t hash = reinterpret_cast<std::uint64_t>(ptr);
	return hash >> 12;
}

void MyHashTable::print() {
	for (size_t i = 0; i < capacity_; i++) {
		if (table_[i] != nullptr) {
			std::cout << "Index " << i << ":\n"
					  << "Memory block address: " << table_[i]->pointer_ << "\n"
					  << "Memory block size: " << table_[i]->size_ << "\n"
					  << "Memory block deleted status: " << (table_[i]->has_deleted_ ? "true" : "false") << std::endl;
		}
	}
}