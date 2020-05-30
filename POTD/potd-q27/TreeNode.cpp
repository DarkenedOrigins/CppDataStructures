#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int getHeight_(TreeNode* subroot){
	if(subroot == NULL){
		return -1;
	}
	return 1+max(getHeight_(subroot->left_), getHeight_(subroot->right_) );
}
int TreeNode::getHeight() {
	return 1 + max (getHeight_(this->left_), getHeight_(this->right_) );
}

