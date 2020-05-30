#include "Queue.h"

Queue::Queue() {
	size_=0;
	head_=NULL;
	tail_=NULL;
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
  return size_;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
	if(size_ == 0){
		return true;
	}else{return false;}
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
	if(head_ == NULL){
		head_= new QNode(value,NULL);
		tail_ = head_;
		size_++;
		return;
	}
	tail_->next = new QNode(value,NULL);
	tail_ = tail_->next;
	size_++;
	return;
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
	if(head_==NULL){return 0;}
	int retval = head_->val;
	QNode* temp = head_;
	head_ = head_->next;
	delete temp;
	size_--;
	return retval;
}
