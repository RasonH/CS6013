#pragma once

#include <mutex>

template <typename T>
class ConcurrentQueue {
 private:
	struct Node {
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;
	int size_;
	std::mutex mutex_;

 public:
	ConcurrentQueue() : head(new Node{T{}, nullptr}), size_(0) {
		tail = head;
	}

	void enqueue(const T& x) {
		Node* node = new Node{x, nullptr};
		std::unique_lock<std::mutex> lock(mutex_);
		if (size_ == 0) {
			head = node;
			tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		size_++;
	}

	bool dequeue(T* ret) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (size_ == 0) {
			return false;
		}
		Node* tmp = head;
		head = head->next;
		tmp->next = nullptr;
		*ret = tmp->data;
		delete tmp;
		size_--;
		return true;
	}

	~ConcurrentQueue() {
		while (head) {
			Node* temp = head->next;
			delete head;
			head = temp;
		}
	}

	int size() const {
		return size_;
	}
};