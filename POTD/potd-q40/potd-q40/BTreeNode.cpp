#include <vector>
#include <algorithm>
#include "BTreeNode.h"


BTreeNode* find(BTreeNode* root, int key) {
    // Your Code Here
	if(root->is_leaf_){
		auto it = std::find(elements_.begin(), elements_.end(), key);
		if ( it  == elements_.end() ){
			return NULL;
		}else{
			return root;
		}
	}
	auto ChildIt = root->children_.begin();
	for(auto ElemIt = elements_.begin(); ElemIt <= elements_.end(); ElemIt++){
		if(key == *ElemIt){
			return root;
		}
		if(key < *ElemIt){
			return find(*ChildIt,key);
		}
		if(ElemIt == elements_.end() ){
			return find(*ChildIt,key);
		}
		ChildIt++;
	}
	return NULL;
}
