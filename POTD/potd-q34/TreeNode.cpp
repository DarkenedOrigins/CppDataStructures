#include "TreeNode.h"
#include <algorithm>

int height(TreeNode* root){
	if(root==NULL){
		return -1;
	}
	int x=height(root->left_);
	int y=height(root->right_);
	if(x>y){
		x=x;
	}else{
		x=y;
	}
	return x+1;
}
int getHeightBalance(TreeNode* root) {
	return height(root->left_)-height(root->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

