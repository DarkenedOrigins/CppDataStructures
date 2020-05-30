#include "Node.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

Node *listUnion(Node *first, Node *second) {
	vector<int> NumsSeen;
	while(first != NULL){
		if( find(begin(NumsSeen), end(NumsSeen), first->data_) == end(NumsSeen) ){
			NumsSeen.push_back(first->data_);
		}
		first = first->next_;
	}
	while(second != NULL){
		if( find(begin(NumsSeen), end(NumsSeen), second->data_) == end(NumsSeen) ){
			NumsSeen.push_back(second->data_);
		}
		second = second->next_;
	}
	Node *StartofList, *node;
	StartofList = new Node;
	StartofList->data_ = NumsSeen[0];
	node = StartofList;
	for(int i=1; i < (int)NumsSeen.size(); i++){
		node->next_ = new Node;
		node->next_->data_ = NumsSeen[i];
		node = node->next_;
	}
	node->next_ = NULL;
	return StartofList;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
