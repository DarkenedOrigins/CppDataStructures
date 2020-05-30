#include "potd.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string stringList(Node *head) {
	if(head == NULL){return "Empty List";}
	std::stringstream stream;
	int count =-1;
	while (head !=NULL){
		count++;
		stream << "Node " << count << ": " << head->data_;
		if(head->next_ != NULL){
			stream << " -> ";
		}
		head = head->next_;
	}
	return stream.str();
}
