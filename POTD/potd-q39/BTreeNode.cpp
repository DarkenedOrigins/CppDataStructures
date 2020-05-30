#include <vector>
#include "BTreeNode.h"


std::vector<int> traverse(BTreeNode* root) {
    std::vector<int> v;
    std::vector<int> temp;
	if(root->is_leaf_){
		v = root->elements_;
		return v;
	}
	auto Cit = root->children_.begin();
	for(auto Eit=root->elements_.begin(); Eit <= root->elements_.end(); ++Eit){
		if(Cit != root->children_.end()){
			temp = traverse(*Cit);
		}
		v.insert(v.end(),temp.begin(),temp.end());
		if(Eit != root->elements_.end() ){
			v.push_back(*Eit);
		}
		Cit++;
	}
    return v;
}
