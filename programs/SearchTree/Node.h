#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

struct Node {

public:
  int count;
  string words;
  Node * right;
  Node * left;
  Node * parent;
  Node(string stringInput);
  Node(const Node & toCopy);
    
};

#endif