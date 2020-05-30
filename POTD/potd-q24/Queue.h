#ifndef _QUEUE_H
#define _QUEUE_H

#include <cstddef>

class Queue {
    public:
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
		Queue();
	private:
		struct QNode{
			int val;
			QNode* next;
			QNode(int value,QNode* pointer):val(value),next(pointer){}
		};
		int size_;
		QNode* head_;
		QNode* tail_;
};

#endif
