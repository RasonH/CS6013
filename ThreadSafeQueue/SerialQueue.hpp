#pragma once

template <typename T>
class SerialQueue{
private:
  struct Node{
	T data;
	Node* next;
  };

  Node* head;
  Node* tail;
  int size_;

public:
  SerialQueue()
	:head(new Node{T{}, nullptr}), size_(0)
  {
	tail = head;
  }


  void enqueue(const T& x){
	Node *node = new Node{x, nullptr};
	if(size_ == 0){
		head = node;
		tail = node;
	}else{
		tail->next = node;
		tail = node;
	}
	size_++;
  }

  bool dequeue(T* ret){
    if(size_ == 0){
		return false;
	}
	Node *tmp = head;
	head = head->next;
	tmp->next = nullptr;
    *ret = tmp->data;
	delete tmp;
	size_--;
	return true;
  }

  ~SerialQueue(){
	while(head){
	  Node* temp = head->next;
	  delete head;
	  head = temp;
	}
  }

  int size() const{ return size_;}  
};
