/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

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
    Node* r = t->right;
    t->right = r->left;
    r->left = t;
    t = r;
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
    Node* l = t->left;
    t->left = l->right;
    l->right = t;
    t = l;
  }

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
  int leftBalanace = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
  int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
  if(balance == -2){
    if(leftBalanace == -1){
      rotateRight(subtree);
    }
  else{
      rotateLeftRight(subtree);
    }
  }

  if(balance == 2){
    if(rightBalance == 1){
      rotateLeft(subtree);
    }
    else{
      rotateRightLeft(subtree);
    }
  }
  subtree->height = max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if(subtree == NULL)
    subtree = new Node(key, value);
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
        // your code here
    } else if (key > subtree->key) {
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
        } else {
            /* one-child remove */
            // your code here
        }
        // your code here
    }
}
