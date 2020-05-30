#include "Node.h"

using namespace std;

void mergeList(Node *first, Node *second) {
	int firstNumNodes=0, secondNumNodes=0;
	Node* temp =first;
	while(temp != NULL){
		temp = temp->next_;
		firstNumNodes++;
	}
	temp = second;
	while(temp!=NULL){
		temp = temp->next_;
		secondNumNodes++;
	}
	int n;
	if(firstNumNodes > secondNumNodes){
		n = secondNumNodes;
	}else{
		n = firstNumNodes;
	}
	for(int i=0; i < n; i++){
		temp = first->next_;
		first->next_=second;
		if(second != NULL){second = second->next_;}
		first->next_->next_ = temp;
		if(temp != NULL){first = temp;}
	}
	if(firstNumNodes == secondNumNodes){return;}
	if(secondNumNodes > firstNumNodes){
		first->next_->next_=second;
		return;
	}
	return;

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

