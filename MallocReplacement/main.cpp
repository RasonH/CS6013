#include <vector>
#include <iostream>
#include "MyMalloc.h"
#include <chrono>

int main(int argc, const char * argv[]) {
	// insert code here...

//    //Begining of the Test:
//    MallocReplace myMalloc;
//    //vector:
//    std::vector<void*> vector;
//
//    // to allocate the pointers:
//    for(int i = 0; i < 100; i++) {
//        void* pointer = myMalloc.allocate(1);
//        vector.push_back(pointer); // store all the pointer in the vector
//    }
//    // to deallocate pointers:
//    for(int i = 0; i < vector.size(); i++){
//        //
//        myMalloc.deallocate(vector[i]);
//    }

	// This criterion is linked to a Learning Outcometesting and benchmarking code:
	//timing:
	MyMalloc myMalloc2;
	std::vector<int> vector2;
	for(int i =0; i< 10000; i++){
		vector2.push_back(rand() % 10000 + 1);
	}

	std::chrono::time_point<std::chrono::system_clock> start, end; // timing start to end
	std::chrono::duration<double> durations; // to time a period of time
	std::vector<void*> myAllocator;

	// timing my own malloc:
	start = std::chrono::system_clock::now();// initialize starting time
	for(int i = 0; i < 10000; i ++){
		void* pointer = myMalloc2.allocate(vector2[i]);
		myAllocator.push_back(pointer); // allocate pointer into the myAllocator

	}
	// deAllocate:
	for(int i = 0; i < 10000; i++){
		myMalloc2.deallocate(myAllocator[i]);

	}
	//end time
	end = std::chrono::system_clock::now();// initialize end time
	durations = end - start;
	std::cout<< "my own Malloc running time: " << durations.count() <<std::endl; // to get malloc running time

	//Timing builtin Malloc:
	std::vector<void*> buildingAllocator;
	start = std::chrono::system_clock::now();// initialize starting time
	for(int i = 0; i < 10000; i++){
		void* pointer = malloc(vector2[i]);
		buildingAllocator.push_back(pointer);

	}
	// free malloc:
	for(int i = 0; i < 10000; i ++){
		free(buildingAllocator[i]);

	}

	end = std::chrono::system_clock::now();// initialize end time
	durations = end - start;
	std::cout<< "builtin malloc running time: " << durations.count() <<std::endl;

	//-> my malloc it is slower than the builtin malloc below
	//my own Malloc running time: 0.016135
	//builtin malloc running time: 0.004542

	return 0;
}