/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <queue>
 #include <stack>
 #include <iostream>

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
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
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
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
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
  if(subtree == NULL)
    return;
  int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
  int leftBalanace = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
  int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
  if(balance < -1){
    if(subtree->right->key > subtree->key)
      rotateRightLeft(subtree);
    if(subtree->right->key < subtree->key)
      rotateLeft(subtree);
  else if(balance > 1){
    if(subtree->left->key < subtree->key)
     rotateLeftRight(subtree);
    if(subtree->left->key > subtree->key)
     rotateRight(subtree);
  }
  subtree->height = max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
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
  if(root == NULL){
    root = new Node(key, value);
    root->height = 0;
    return;
  }
  if(subtree->key > key) {
    if(subtree->left == NULL)
      subtree->left = new Node(key,value);
    else
      insert(subtree->left, key, value);
  } else if(subtree->key < key) {
    if(subtree->right == NULL)
      subtree->right = new Node(key, value);
    else
      insert(subtree->right, key, value);
  } else
    return;
  rebalancekey(subtree, key);
}

template <class K, class V>
void AVLTree<K, V>::rebalancekey(Node *& subtree, const K& key) {
  int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
  if (balance == 0)
    return;
  if (balance > 1) {
    if(subtree->left->key < key)
        rotateLeftRight(subtree);
    if(subtree->left->key > key)
        rotateRight(subtree);
  } else if(balance < -1) {
    if(subtree->right->key > key)
        rotateRightLeft(subtree);
    if(subtree->right->key < key)
        rotateLeft(subtree);
  }
  subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
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
        remove(subtree->right, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
          Node * temp = subtree;
          delete temp;
          subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * iop = getIOP(subtree->left, true);
            swap(iop, subtree);
            if(iop->left != NULL) {
              swap(iop->left,iop);
              removeNode(subtree, iop->left->key);
            } else {
              removeNode(subtree, iop->key);
            }
        } else {
            /* one-child remove */
            if(subtree->left != NULL) {
              Node * iop = getIOP(subtree->left, true);
              swap(iop, subtree);
              if(iop->left != NULL) {
                swap(iop->left,iop);
                removeNode(subtree, iop->left->key);
              } else {
                removeNode(subtree, iop->key);
              }
            }
            if(subtree->right != NULL) {
              Node * iop = getIOP(subtree->right, false);
              swap(iop, subtree);
              if(iop->right != NULL) {
                swap(iop->right,iop);
                removeNode(subtree, iop->right->key);
              } else {
                removeNode(subtree, iop->key);
              }
            }
        }
        if (subtree == NULL) return;
int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
if (balance == 0) return;
if (balance > 1) {
if(heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) >= 0)
    rotateRight(subtree);
if(heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) < 0)
    rotateLeftRight(subtree);
} else if(balance < -1) {
if(heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) <= 0)
    rotateLeft(subtree);
if(heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left)  > 0)
    rotateRightLeft(subtree);
    }
}
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getIOP(Node* root, bool max) {
  queue<Node *> q;
  stack<Node *> s;
  Node * temp = root;
  q.push(temp);
  while(!q.empty()) {
    temp = q.front();
    q.pop();
    if(temp->left != NULL) q.push(temp->left);
    if(temp->right != NULL) q.push(temp->right);
    s.push(temp);
  }
  if(max) return getMax(s);
  else return getMin(s);
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getMax(stack<Node*> s) {
  Node * max = s.top();
  while(!s.empty()) {
    Node * curr = s.top();
    if(curr->key > max->key) {
      max = curr;
    }
    s.pop();
  }
  return max;
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getMin(stack<Node*> s) {
  Node * min = s.top();
  while(!s.empty()) {
    Node * curr = s.top();
    if(curr->key < min->key) {
      min = curr;
    }
    s.pop();
  }
  return min;
}

template <class K, class V>
void AVLTree<K,V>::removeNode(Node *& root, K key) {
    if(root == NULL) return;
    if (root->key == key) {
        delete root;
        root = NULL;
        return;
    }
    removeNode(root->right, key);
    removeNode(root->left, key);
}
