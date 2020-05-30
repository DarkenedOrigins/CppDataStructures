#include "TreeNode.h"
#include <stdlib.h>

int height(TreeNode* root){
	if(root == NULL)return -1;
	int x = height(root->left_);
	int y = height(root->right_);
	if(x>y) return x+1;
	else return y+1;
}
bool isHeightBalanced(TreeNode* root) {
	if(abs(height(root->left_)-height(root->right_)) <2)
		return true;
	else return false;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

