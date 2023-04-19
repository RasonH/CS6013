#include "SerialQueue.hpp"
#include <cassert>

int main() {

	// Test static allocation
	{
		SerialQueue<int> q;
		assert(q.size() == 0);

		// Enqueue elements
		for (int i = 0; i < 5; i++) {
			q.enqueue(i);
			assert(q.size() == i + 1);
		}

		// Dequeue elements
		int x;
		for (int i = 0; i < 5; i++) {
			assert(q.dequeue(&x));
			assert(x == i);
			assert(q.size() == 4 - i);
		}

		// Test dequeue on empty queue
		assert(!q.dequeue(&x));
		assert(q.size() == 0);
	}

	// Test dynamic allocation

	{
		SerialQueue<int> q;
		assert(q.size() == 0);

		// Enqueue elements
		for (int i = 0; i < 10; i++) {
			q.enqueue(i);
			assert(q.size() == i + 1);
		}

		// Dequeue elements
		int x;
		for (int i = 0; i < 10; i++) {
			assert(q.dequeue(&x));
			assert(x == i);
			assert(q.size() == 9 - i);
		}

		// Test dequeue on empty queue
		assert(!q.dequeue(&x));
		assert(q.size() == 0);
	}


	// Test dynamic deallocation

	{
		SerialQueue<int> *q = new SerialQueue<int>();
		assert(q->size() == 0);

		// Enqueue elements
		for (int i = 0; i < 10; i++) {
			q->enqueue(i);
			assert(q->size() == i + 1);
		}

		// Dequeue elements
		int x;
		for (int i = 0; i < 10; i++) {
			assert(q->dequeue(&x));
			assert(x == i);
			assert(q->size() == 9 - i);
		}

		// Test dequeue on empty queue
		assert(!q->dequeue(&x));
		assert(q->size() == 0);

		// Delete queue
		delete q;
	}


	return 0;
}