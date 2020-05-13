#include <iostream>
#include "Node.h"

using namespace std;


Node::Node() { //constructor of empty node
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
    counter = 0;
}

Node::Node(string small, Node * par) { //constructor is only 1 string passed in
    this->small = small;
    left = 0;
    middle = 0;
    right = 0;
    parent = par;
    counter = 1;
}

Node::Node(string small, string large, Node * par) { //constructor if 2 strings passed in
    this->small = small;
    this->large = large;
    left = 0;
    middle = 0;
    right = 0;
    parent = par;
    counter = 2;
}

bool Node::isFull() const { //returns true is node has 2 values, false if 0 or 1
        
    if (counter == 2) {
        return true;
    }
    
    return false;
}

bool Node::isLeaf() const { //returns true if node is leaf node
    if (left == 0 && middle == 0 && right == 0) {
        return true;
    }
    
    return false;
}

void Node::changeCounter(int count) { //sets counter
    counter = count;
}

void Node::addValue(string add) { //adds value to node if able
    if (small.empty()) {
        small = add;
        changeCounter(1);
    } else if (add > small) {
        large = add;
        changeCounter(2);
    } else if (add < small) {
        large = small;
        small = add;
        changeCounter(2);
    }
}

void Node::addChild(Node * newChild) { //adds explicit parameter as child to implicit parameter
    if (newChild == 0) {
        return;
    }
    
    if (this->left != 0 && this->middle != 0 && this->right != 0) {
        return;
    } 
    
    newChild->parent = this;
    if (newChild->small < this->small || !this->left) {
        if (newChild->small < this->small && !this->right) {
            this->right = this->left;
        }
        this->left = newChild;
        
    } else if ((!this->large.empty() && !this->middle) || (!this->left && this->right))  {
        if (newChild->small < this->large) {
            this->middle = newChild;
        }
    } else {
        this->right = newChild;
    
    }
    
}

bool Node::maxChildren() const { //returns true if node has 3 children
    if (this->left && this->middle && this->right) {
        return true;
    }
    
    return false;

}

Node * Node::swapSuccessor(const string & swap) { //swaps implicit parameter with inOrder successor's place and returns new location
    string temp = "";
    if (swap == small && !large.empty()) {
        string temp = small;
        small = middle->small;
        middle->small = temp;
        return middle;
    } else if (swap == large) {
        right->small = temp;        
        return right;
    } else {
        string temp = small;
        small = right->small;
        right->small = temp;
        return right;
    }
    
}

bool Node::empty() const { //returns empty if node has no values
    if (small.empty() && large.empty()) {
        return true;
    }
    
    return false;
}

Node * Node::rightSibling() const { //returns adjacent right sibling if exists
    if (this->parent) {
        Node * par = this->parent;
        if (this == par->left && par->middle) {
            return par->middle;
        } else if (this == par->middle) {
            return par->right;
        } else if (this == par->left && par->right) {
            return par->right;
            
        } else {
            return 0;
        }
    }
    
    return 0;
}

Node * Node::leftSibling() const { //returns adjacent left sibling if exists
    if (this->parent) {
        Node * par = this->parent;
        if (this == par->right && par->middle) {
            return par->middle;
        } else if (this == par->middle) {
            return par->left;
        } else if (this == par->right && par->left) {
            return par->left;
        } else {
            return 0;
        }
    }
    
    return 0;
}

string Node::validToRedistribute() const { //if has viable sibling for redistribution, returns string to which sibling, else returns empty string
    Node * p = this->parent;
    
    if (p->isFull()) {
        if (this == p->left) {
            if (p->middle->isFull()) {
                return "middle";
            } else if (p->right->isFull()) {
                return "right";
            }
        } else if (this == p->middle) {
            if (p->right->isFull()) {
                return "right";
            } else if (p->left->isFull()) {
                return "left";
            }
        } else {
            if (p->middle->isFull()) {
                return "middle";
            } else if (p->left->isFull()) {
                return "left";
            }
        }
    } else {
        if (this == p->left) {
            if (p->right->isFull()) {
                return "right";
            }
        } else {
            if (p->left->isFull()) {
                return "left";
            }
        }
    }
    
    return "";
}

void Node::removeValue(const string & toRemove) { //removes toRemove from implicit node
    if (small == toRemove) {
        small = large;
        large = "";
        if (small.empty() && large.empty()) {
            counter = 0;
        } else {
            counter = 1;
        }
        
    } else {
        large = "";
        counter = 1;
    }
}

void Node::transferChildren(Node * transferee) { //transfers children from explicit to implicit
    addChild(transferee->left);
    addChild(transferee->middle);
    addChild(transferee->right);
}

Node * Node::findSuccessor() const { //returns successor
    if (middle) {
        return middle;
    } 
    if (right) {
        return right;
    }
    return left;
}