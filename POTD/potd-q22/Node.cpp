#include "Node.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

Node *listSymmetricDifference(Node *first, Node *second) {
	if(first == second){return NULL;}
	if(first == NULL && second == NULL){
		return NULL;
	}
	vector<int> NumsInOne;
	vector<int> NumsInTwo;
	vector<int> Final;
	while(first != NULL){
		NumsInOne.push_back(first->data_);
		first = first->next_;
	}
	while(second != NULL){
		NumsInTwo.push_back(second->data_);
		second = second->next_;
	}
	vector<int>::iterator VecIt;
	VecIt = begin(NumsInOne);
	while(VecIt != end(NumsInOne) ){
		if( find( begin(NumsInTwo),end(NumsInTwo), *VecIt) == end(NumsInTwo) && find(begin(Final), end(Final), *VecIt) == end(Final) ){
			Final.push_back(*VecIt);
		}
		VecIt++;
	}
	VecIt = begin(NumsInTwo);
	while(VecIt != end(NumsInTwo) ){
		if( find( begin(NumsInOne),end(NumsInOne),*VecIt) == end(NumsInOne) && find(begin(Final), end(Final), *VecIt) == end(Final)){
			Final.push_back(*VecIt);
		}
		VecIt++;
	}
	if(Final.empty() ){ return NULL;}
	VecIt = begin(Final);
	Node* head = new Node;
	head->data_=*VecIt;
	VecIt++;
	Node* CurrNode = head;
	while(VecIt != end(Final)){
		CurrNode->next_ = new Node;
		CurrNode->next_->data_=*VecIt;
		CurrNode = CurrNode->next_;
		VecIt++;
	}
	CurrNode->next_ = NULL;
	return head;
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
