#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include <iostream>
#include "Node.h"
using namespace std;

class AVLTree {

private:
  Node * root;

private:
  void printBalanceFactors(Node *printNode);
  int height(Node* n);
  Node* findUnbalancedNode(Node* start);
  Node* rotateLeft(Node*);
  Node* rotateRight(Node*);
  void rotate(Node* &start);
  void visualizeTree(ofstream & outFS, Node *n);
  
public:
  AVLTree();
  int balanceFactor(Node* curr);
  void insert(const string &s);
  void printBalanceFactors(); //recursive
  void visualizeTree(const string &outputFilename);
};

#endif