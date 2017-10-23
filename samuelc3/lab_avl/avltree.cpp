/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <queue>
 #include <stack>
 #include <iostream>

 using namespace std;


 template <class K, class V>
 V AVLTree<K, V>::find(const K& key) const {
     return find(root, key);
 }

 template <class K, class V>
 V AVLTree<K, V>::find(Node* subtree, const K& key) const {
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
    Node* rLeft = r->left;
    r->left = t;
    t->right = rLeft;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    r->height = max(heightOrNeg1(r->left),heightOrNeg1(r->right))+1;
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
    Node* lRight = l->right;
    l->right = t;
    t->left = lRight;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    l->height = max(heightOrNeg1(l->left),heightOrNeg1(l->right))+1;
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
  int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
  if (balance == 0)
    return;
    if(balance < -1) {
      if(subtree->right->key > key)
          rotateRightLeft(subtree);
      if(subtree->right->key < key)
          rotateLeft(subtree);
    }
  else if (balance > 1) {
    if(subtree->left->key < key)
        rotateLeftRight(subtree);
    if(subtree->left->key > key)
        rotateRight(subtree);
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
  if (subtree == NULL) return;

  if(key < subtree->key) remove(subtree->left, key);
  else if (key > subtree->key) remove(subtree->right, key);
  else {
      if (subtree->left == NULL && subtree->right == NULL) {
          /* no-child remove */
          Node * temp = subtree;
          delete temp;
          subtree = NULL;
      } else if (subtree->left != NULL && subtree->right != NULL) {
          /* two-child remove */
          Node * iop = getIOP(subtree->left, true);
          swap(iop, subtree);
          if(iop->left == NULL) {
            removeN(subtree, iop->key);
          } else {
            swap(iop->left,iop);
            removeN(subtree, iop->left->key);
          }
      } else {
          /* one-child remove */
          if(subtree->left != NULL) {
            Node * iop = getIOP(subtree->left, true);
            swap(iop, subtree);
            if(iop->left == NULL) {
              removeN(subtree, iop->key);
            } else {
              swap(iop->left,iop);
              removeN(subtree, iop->left->key);
            }
          }
          if(subtree->right != NULL) {
            Node * iop = getIOP(subtree->right, false);
            swap(iop, subtree);
            if(iop->right != NULL) {
              swap(iop->right,iop);
              removeN(subtree, iop->right->key);
            } else {
              removeN(subtree, iop->key);
            }
          }
      }
  }

  if (subtree == NULL) return;
int balance = getHeightBalance(subtree);
if (balance == 0) return;
if (balance > 1) {
  if(getHeightBalance(subtree->left) >= 0)
      rotateRight(subtree);
  if(getHeightBalance(subtree->left) < 0)
      rotateLeftRight(subtree);
} else if(balance < -1) {
  if(getHeightBalance(subtree->right) <= 0)
      rotateLeft(subtree);
  if(getHeightBalance(subtree->right) > 0)
      rotateRightLeft(subtree);
}
}

template <class K, class V>
int AVLTree<K,V>::getHeightBalance(Node* root) {
  if (root == NULL) return 0;
  return heightOrNeg1(root->left)-heightOrNeg1(root->right);
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getIOP(Node* root, bool max) {
  stack<Node *> s;
  queue<Node *> q;
  Node * temp = root;
  q.push(temp);
  while(!q.empty()) {
    temp = q.front();
    q.pop();
    if(temp->left != NULL) q.push(temp->left);
    if(temp->right != NULL) q.push(temp->right);
    s.push(temp);
  }
  if(max)
    return getMax(s);
  else
    return getMin(s);
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getMax(stack<Node*> s) {
  Node * maxp = s.top();
  while(!s.empty()) {
    Node * curr = s.top();
    if(curr->key > maxp->key) {
      maxp = curr;
    }
    s.pop();
  }
  return maxp;
}

template <class K, class V>
typename AVLTree<K, V>::Node * AVLTree<K,V>::getMin(stack<Node*> s) {
  Node * pmin = s.top();
  while(!s.empty()) {
    Node * curr = s.top();
    if(curr->key < pmin->key) {
      pmin = curr;
    }
    s.pop();
  }
  return pmin;
}

template <class K, class V>
void AVLTree<K,V>::removeN(Node *& root, K key) {
    if(root == NULL) return;
    if (root->key == key) {
      Node * temp = root;
        delete temp;
        root = NULL;
        return;
    }
    removeN(root->right, key);
    removeN(root->left, key);
}
