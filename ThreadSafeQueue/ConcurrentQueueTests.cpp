#include <iostream>
#include <vector>
#include <thread>
#include "ConcurrentQueue.hpp"

bool testQueue(int num_producers, int num_consumers, int num_ints) {
	std::vector<std::thread> threads;
	threads.reserve(num_producers + num_consumers);

	ConcurrentQueue<int> queue;

	// Create producer threads
	for (int i = 0; i < num_producers; i++) {
		threads.emplace_back([&queue, num_ints]() {
		  for (int j = 0; j < num_ints; j++) {
			  queue.enqueue(j);
		  }
		});
	}

	// Create consumer threads
	for (int i = 0; i < num_consumers; i++) {
		threads.emplace_back([&queue, num_ints]() {
		  int value;
		  for (int j = 0; j < num_ints; j++) {
			  while (!queue.dequeue(&value)) {
				  // Wait for an element to be available
			  }
		  }
		});
	}

	// Wait for all threads to finish
	for (std::thread& t : threads) {
		t.join();
	}

	// Check if the queue size is correct
	int expected_size = (num_producers - num_consumers) * num_ints;
	int actual_size = queue.size();
	assert(actual_size == expected_size && "Test failed: queue size is incorrect.");

	return true;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <num_producers> <num_consumers> <num_ints>" << std::endl;
		return 1;
	}

	int num_producers = std::stoi(argv[1]);
	int num_consumers = std::stoi(argv[2]);
	int num_ints = std::stoi(argv[3]);

	assert(testQueue(num_producers, num_consumers, num_ints) && "Test failed.");

	std::cout << "Test passed!" << std::endl;
	return 0;
}