#include "potd.h"
#include <iostream>

using namespace std;

string stringList(Node *head) {
    if (head == NULL) {
        return "Empty list";
    }

    string out = "";

    for(int i=0; head != NULL; i++, head = head->next_) {
        if (i > 0) 
            out = out + " -> ";
        out = out + "Node " + to_string(i) + ": " + to_string(head->data_);
    }

    return out;
}
void insertSorted(Node **head, Node *item){
	if(*head == NULL){
		*head = item;
		item->next_ = NULL;
		return;
	}
	Node* Nptr = *head;
	if(Nptr->data_>=item->data_){
		*head=item;
		item->next_=Nptr;
		return;
	}
	while(Nptr->next_ != NULL){
		if(Nptr->next_->data_ >= item->data_){
			item->next_ = Nptr->next_;
			Nptr->next_=item;
			return;
		}
		Nptr = Nptr->next_;
	}
	Nptr->next_ = item;
	item->next_=NULL;
	return;
}
