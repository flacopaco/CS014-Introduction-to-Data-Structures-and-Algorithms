#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(string i, int c, Node *l, Node *r, Node *p) {
    item = i;
	count = c;
	left = l;
	right = r;
	parent = p;
}