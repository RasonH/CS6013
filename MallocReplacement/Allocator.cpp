#include "Allocator.h"
#include <sys/mman.h>
#include <unistd.h>

Allocator::Allocator() {
	// Initialize the hash table
	alloc_table_ = MyHashTable();
}

void* Allocator::allocate(size_t bytesToAllocate) {
	// Round up the allocation size to the next multiple of the page size
	size_t pageSize = sysconf(_SC_PAGESIZE);
	size_t numPages = (bytesToAllocate + pageSize - 1) / pageSize; // in order to round up allocation size
	size_t totalSize = pageSize * numPages;

	// Allocate memory with mmap
	void* ptr = mmap(nullptr, totalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED){
		std::cerr << "mmap failed - allocate(size_t bytesToAllocate)" << std::endl;
		exit(1);
	}

	// Insert the returned pointer and the allocation size in the hash table
	MyHashNode* node = static_cast<MyHashNode *> (mmap(nullptr, 8, PROT_READ | PROT_WRITE,
													   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
	node->pointer_ = ptr;
	node->size_ = totalSize;
	alloc_table_.insert(node);

	return ptr;
}

void Allocator::deallocate(void* ptr) {
	// Find the node with the corresponding pointer in the hash table
	// they should have unique pointer_ for each node, but they might have a same hash() in the table
	size_t size = alloc_table_.findAndRemove(ptr);

	// Deallocate the memory with munmap
	if (munmap(ptr, size) != 0){
		std::cerr << "munmap failed - deallocate(void* ptr)" << std::endl;
		exit(1);
	}
}