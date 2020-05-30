#include "Stack.h"
using namespace std;

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
	return StackVector.size();
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
  return StackVector.empty();
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
	StackVector.push_back(value);
	return;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
	int value = StackVector.back();
	StackVector.pop_back();
  return value;
}
