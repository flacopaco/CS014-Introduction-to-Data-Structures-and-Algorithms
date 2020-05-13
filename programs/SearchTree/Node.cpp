#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(string stringInput) {
    words = stringInput;
    count = 1;
    right = 0;
    left = 0;
    parent = 0;
}

Node::Node(const Node & toCopy) {
    words = toCopy.words;
    count = toCopy.count;
}