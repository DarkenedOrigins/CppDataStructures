#include "TreeNode.h"
#include <iostream>

TreeNode* findIOP(TreeNode* root){
	if(root == NULL ){return NULL;}
	root = root->left_;
	TreeNode* temp = root;
	while(root->right_ != NULL){
		temp = root;
		root = root->right_;
	}
	temp->right_ = root->left_;
	return root;
}
TreeNode * deleteNode(TreeNode* root, int key) {
	if(root==NULL) return NULL;
	if(root->val_ == key){
		if(root->right_ == root->left_){
			delete root;
			return NULL;
		}
		if(root->right_==NULL){
			TreeNode* temp = root->left_;
			delete root;
			return temp;
		}
		if(root->left_ == NULL){
			TreeNode* temp = root->right_;
			delete root;
			return temp;
		}
		TreeNode* NewNode = findIOP(root);
		NewNode->left_ = root->left_;
		NewNode->right_ = root->right_;
		delete root;
		return NewNode;
	}
	root->left_ = deleteNode(root->left_, key);
	root->right_ = deleteNode(root->right_,key);
	return root;
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
