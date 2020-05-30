/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

// #include <iostream>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    y->height += 1;
    t->height -= 1;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    y->height += 1;
    t->height -= 1;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if (subtree == NULL) return;
  int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
  if (balance == -2) {
      int leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if (leftBalance == -1) {
          rotateRight(subtree);
      } else {
          rotateLeftRight(subtree);
      }
  } else if (balance == 2) {
      int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (rightBalance == 1) {
          rotateLeft(subtree);
      } else {
          rotateRightLeft(subtree);
      }
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if (subtree == NULL) {
      subtree = new Node(key, value);
  }
  else if (key < subtree->key) {
      insert(subtree->left, key, value);
      rebalance(subtree);
  }
  else if (key > subtree->key) {
      insert(subtree->right, key, value);
      rebalance(subtree);
  }

  subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* IOP = subtree->left;
            while (IOP->right != NULL)
                IOP = IOP->right;
            swap(IOP, subtree);
            remove(subtree->left, IOP->key);
        } else {
            /* one-child remove */
            if (subtree->left != NULL) {
                Node* next = subtree->left;
                delete subtree;
                subtree = next;
            } else {
                Node* next = subtree->right;
                delete subtree;
                subtree = next;
            }
        }
        // your code here
    }
}
