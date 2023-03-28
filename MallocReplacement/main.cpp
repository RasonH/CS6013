#include <vector>
#include "Allocator.h"

int main() {
	// For my assert test, I tested the growing size, lazy delete, deallocating and to see if using for loop to allocate would success and delete all the addresses afterwards.
	Allocator allocator, allocator1, allocator2;
	allocator.allocate(100);
	//Testing size increasing
	assert(allocator.alloc_table_.table_size_ == 1);
	assert(allocator.alloc_table_.capacity_ == 11);


	// Testing growing size. If the size >= 0.5 then grow size
	for (int i = 0; i < 6; i++) {
		allocator.allocate(100 + i);
	}
	assert(allocator.alloc_table_.table_size_ == 7);
	assert(allocator.alloc_table_.capacity_ == 22);
//	for (int i = 0; i < allocator.alloc_table_.capacity_; i++){
//		if(!allocator.alloc_table_.table_[i]->has_deleted_){
//			allocator.deallocate(allocator.alloc_table_.table_[i]->pointer_);
//		}
//	}
//
	// Testing deallocate
	void *addr0 = allocator1.allocate(100);
	void *addr1 = allocator1.allocate(101);
	void *addr2 = allocator1.allocate(102);
	void *addr3 = allocator1.allocate(103);
	void *addr4 = allocator1.allocate(104);
	void *addr5 = allocator1.allocate(105);

	// When deallocate, it will check if unmap return 0 or -1.
	allocator1.deallocate(addr0);
	allocator1.deallocate(addr2);
	allocator1.deallocate(addr4);
	assert(allocator1.alloc_table_.table_size_ == 3);

	// Print table and can see that remove index member variable is set to 1 which is true, meaning lazy delete success
	std::cout << "---------------------------------" << std::endl;
	allocator1.alloc_table_.print();
	std::cout << "---------------------------------" << std::endl;
	allocator1.deallocate(addr1);
	allocator1.deallocate(addr3);
	allocator1.deallocate(addr5);
	std::cout << "---------------------------------" << std::endl;
	allocator1.alloc_table_.print();
	std::cout << "---------------------------------" << std::endl;

	void *arr[10];
	for (int i = 0; i < 7; ++i) {
		arr[i] = allocator2.allocate(100);
	}

	for (int i = 0; i < 7; ++i) {
		allocator2.deallocate(arr[i]);
	}
	// Check if the item in the array are all lazy deleted
	for (int i = 0; i < allocator2.alloc_table_.capacity_; ++i) {
		if (allocator2.alloc_table_.table_[i] != nullptr) assert(allocator2.alloc_table_.table_[i]->has_deleted_);
	}
	assert(allocator2.alloc_table_.table_size_ == 0);


	// Time tests for the allocator and builtin functions
	// test by directly recording the custom allocator time and the builtin function time
	std::cout << "---------------------------------" << std::endl;
	constexpr size_t NUM_ALLOCS = 100000;
	constexpr size_t ALLOC_SIZE = 32;

	std::vector<void*> malloc_ptrs;
	std::vector<void*> alloc_ptrs;
	std::cout << "Time test:" << std::endl;
	// Benchmark malloc
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < NUM_ALLOCS; i++) {
		void* ptr = std::malloc(ALLOC_SIZE);
		malloc_ptrs.push_back(ptr);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> malloc_time = end - start;
	std::cout << "Time taken by malloc: " << malloc_time.count() << " ms" << std::endl;

	// Free memory allocated by free
	start = std::chrono::high_resolution_clock::now();
	for (void* ptr : malloc_ptrs) {
		std::free(ptr);
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> free_time = end - start;
	std::cout << "Time taken by delete: " << malloc_time.count() << " ms" << std::endl;

	// test custom allocator
	Allocator allocator3;
	start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < NUM_ALLOCS; i++) {
		void* ptr = allocator3.allocate(ALLOC_SIZE);
		alloc_ptrs.push_back(ptr);
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> alloc_time = end - start;
	std::cout << "Time taken by custom allocator: " << alloc_time.count() << " ms" << std::endl;

	// Free memory allocated by our custom allocator
	start = std::chrono::high_resolution_clock::now();
	for (void* ptr : alloc_ptrs) {
		allocator3.deallocate(ptr);
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> dealloc_time = end - start;
	std::cout << "Time taken by custom delete: " << dealloc_time.count() << " ms" << std::endl;
	std::cout << "---------------------------------" << std::endl;

	return 0;
}

