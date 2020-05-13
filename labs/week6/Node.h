#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

struct Node {

public:
  string item;
  int count;
  Node* left;
  Node* right;
  Node* parent;
  Node(string i, int c = 0, Node *l = 0, Node *r = 0, Node *p = 0);
};

#endif