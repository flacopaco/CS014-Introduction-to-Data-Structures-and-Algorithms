#ifndef __BSTREE_H__
#define __BSTREE_H__
#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class BSTree {

private:
  Node * root = 0;


private:
  void preOrder(Node *) const;
  void inOrder(Node * ) const;
  void postOrder(Node * ) const;  
  bool search(Node *, const string &) const;
  int heightHelper(Node *, int &) const;
  void remove(Node *, Node *, const string &);
  void remoteRemove(Node *, Node *, const string &);
  string findMax(Node *) const;
  string findMin(Node *) const;
  int countFinder(Node *, const string &) const;
  //void destructorTraverse(Node *);
  
public:
  
  ~BSTree(); //destructor
  void insert(const string &);
  bool search(const string &) const; //recursive
  void inOrder( ) const; //recursive
  void postOrder( ) const; //recursive
  void preOrder( ) const; //recursive
  string largest( ) const;
  string smallest( ) const;
  int height(const string &) const;
  void remove(const string &); //recursive
};

#endif