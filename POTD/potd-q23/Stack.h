#ifndef _STACK_H
#define _STACK_H

#include <cstddef>
#include <vector>
using namespace std;
class Stack {
public:
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
private:
  vector<int> StackVector;
};

#endif
