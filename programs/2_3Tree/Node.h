#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

private:
  string small;
  string large;
  int counter;
  Node *left;
  Node *middle;
  Node *right;
  Node *parent;
  
public:
  Node();
  Node(string, Node *);
  Node(string, string, Node *);
  bool isFull() const;
  bool isLeaf() const;
  bool maxChildren() const;
  void changeCounter(int count);
  void addValue(string add);
  void addChild(Node *);
  Node * swapSuccessor(const string &);
  bool empty() const;
  Node * rightSibling() const;
  Node * leftSibling() const;
  void removeValue(const string &);
  void transferChildren(Node *);
  Node * findSuccessor() const;
  string validToRedistribute() const;  
  

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif
