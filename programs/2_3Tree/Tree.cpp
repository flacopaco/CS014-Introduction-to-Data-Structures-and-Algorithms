#include <iostream>
using namespace std;
#include "Tree.h"
#include "Node.h"

Tree::Tree( ) { //constructs empty tree
    root = 0;
}

Tree::~Tree( ) { //destructor
        while (root) {
        Node * cur = root;
        string toRemove = cur->small;
        remove(toRemove);
    }
    
}

void Tree::insert(const string & input) { 
    if (root == 0) { ////if empty tree, construcst root
        root = new Node(input, 0);
        return;
    } else {
        Node * cur = root;
        while (cur != 0) { //iterates until finds appropriate leaf
            if (cur->isLeaf()) {
                if (!cur->isFull()) { //if leaf is not full, simply appends value to node
                    cur->addValue(input);
                    return;
                    
                } else {
                    split(cur, input, 0, 0, 0, 0); //splits leaf if adding would cause invalid node
                    
                    return;
                }
            } else if (input < cur->small) {
                cur = cur->left;
            } else if (!cur->large.empty() && input < cur->large) {
                cur = cur->middle;
            } else {
                
                cur = cur->right;
            }
            
        }
        
    }

}

Node * Tree::split(Node * n, string input, Node * lefty, Node * midLeft, Node * midRight, Node * righty) {

    Node * p;
    if (n == root) {
        p = new Node();
        
    } else {
        p = n->parent;
    }
    
    string smallest;
    string middle;
    string largest;
    
    if (input < n->small && input < n->large) {
        smallest = input;
        middle = n->small;
        largest = n->large;
    } else if (input > n->small && input < n->large) {
        smallest = n->small;
        middle = input;
        largest = n->large;
    } else {
        smallest = n->small;
        middle = n->large;
        largest = input;
    }
    //above sorts between the conceptual three values to find which to move up to parent
    
    Node * n1 = new Node(smallest, p);
    Node * n2 = new Node(largest, p);
    
    if (!n->isLeaf()) { //if recursively called, adds children to split parent's children
        n1->addChild(lefty);
        n1->addChild(midLeft);
        n2->addChild(midRight);
        n2->addChild(righty);
    }
    

    if (!p->maxChildren()) { //disconnects n before adding n1 and n2
        if (n == p->right) {
            p->right = 0;
        } else {
            p->left = 0;
        }
    }
    
    string x = middle;
    
    if (p->isFull()) {
        Node * rightMost;
        Node * middleRight;
        Node * middleLeft;
        Node * leftMost;
        
        if (n == p->right) { //finds out which case the internal splice is
            rightMost = n2;
            middleRight = n1;
            middleLeft = p->middle;
            leftMost = p->left;
        } else if (n == p->middle) {
            rightMost = p->right;
            middleRight = n2;
            middleLeft = n1;
            leftMost = p->left;
        } else {
            rightMost = p->right;
            middleRight = p->middle;
            middleLeft = n2;
            leftMost = n1;
        }
        
        p = split(p, x, leftMost, middleLeft, middleRight, rightMost); //calls recursive split for internal split of a 3/4 node
        if (n == root) {
            root = p;
        }
    } else {
        p->addValue(x);
        p->addChild(n1);
        p->addChild(n2); 
        
        if (n == root) {
            root = p;
        }
    }
    
    return n1;


}

void Tree::inOrder( ) const {
    inOrder(root);
}

void Tree::inOrder(Node * cur) const {
    if (cur) {
        inOrder(cur->left);
        cout << cur->small << ", ";
        if (cur->middle) {
            inOrder(cur->middle);
        }
        if (!cur->large.empty()) {
            cout << cur->large << ", ";
        }
        inOrder(cur->right);
    }
}

void Tree::postOrder( ) const {
    postOrder(root);
}

void Tree::postOrder(Node * cur) const {
    if (cur) {
        if (cur->counter == 2) {
            postOrder(cur->left);
            postOrder(cur->middle);
            cout << cur->small << ", ";
            postOrder(cur->right);
            if (!cur->large.empty()) {
                cout << cur->large << ", ";
            }
        } else {
            postOrder(cur->left);
            postOrder(cur->right);
            cout << cur->small << ", ";
        }
    }
}

void Tree::preOrder() const {
    preOrder(root);
}

void Tree::preOrder(Node * cur) const {
    if (cur) {
        if (cur->counter == 2) {
            cout << cur->small << ", ";
            preOrder(cur->left);
            if (!cur->large.empty()) {
                cout << cur->large << ", ";
            }
    
            preOrder(cur->middle);
            preOrder(cur->right);
        } else {
            cout << cur->small << ", ";
            preOrder(cur->left);
            preOrder(cur->right);
        }
    }
}

void Tree::remove(const string & toRemove) {
    
    Node * node = nodeSearch(toRemove); //returns the node that the word is found in
    Node * leafNode;
    
    if (node) {
        if (!node->isLeaf()) {
            leafNode = node->swapSuccessor(toRemove); //swaps places with inOrder succesoor if not in a leaf
        } else {
            leafNode = node;
        }
        
        leafNode->removeValue(toRemove);
        
        if (leafNode->empty()) {
            fix(leafNode);
        }
        
    }
}

void Tree::fix(Node * n) { //either merges, deletes, or redistributes
    bool redistributed = false;
    
    if (n == root) {
        if (n->isLeaf()) {
            delete n;
            n = 0;
            root = 0;   
        } else {
            root = root->findSuccessor();
        }
    } else {
        Node * p = n->parent;
        
        if (!n->validToRedistribute().empty()) { //needs to redistribute
            string redistributeFrom = n->validToRedistribute(); //returns string that identifies where to redistribute from
            
            if (p->isFull()) { //if a 3 node
                if (redistributeFrom == "left" && n == p->middle) {
                    n->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->left->large);
                    p->left->removeValue(p->left->large);
                } else if (redistributeFrom == "left" && n == p->right) {
                    n->addValue(p->large);
                    p->removeValue(p->large);
                    p->addValue(p->middle->small);
                    p->middle->removeValue(p->middle->small);
                    p->middle->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->left->large);
                    p->left->removeValue(p->left->large);
                } else if (redistributeFrom == "right" && n == p->middle) {
                    n->addValue(p->large);
                    p->removeValue(p->large);
                    p->addValue(p->right->small);
                    p->right->removeValue(p->right->small);
                } else if (redistributeFrom == "right" && n == p->left) {
                    n->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->middle->small);
                    p->middle->removeValue(p->middle->small);
                    p->middle->addValue(p->large);
                    p->removeValue(p->large);
                    p->addValue(p->right->small);
                    p->right->removeValue(p->right->small);
                } else if (redistributeFrom == "middle" && n == p->right) {
                    n->addValue(p->large);
                    p->removeValue(p->large);
                    p->addValue(p->middle->large);
                    p->middle->removeValue(p->middle->large);
                } else if (redistributeFrom == "middle" && n == p->left) {
                    n->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->middle->small);
                    p->middle->removeValue(p->middle->small);
                }
            } else { //else a 2 node
                if (redistributeFrom == "right") {
                    n->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->right->small);
                    p->right->removeValue(p->right->small);
                } else {
                    n->addValue(p->small);
                    p->removeValue(p->small);
                    p->addValue(p->left->large);
                    p->left->removeValue(p->left->large);
                }
            }
            
            if (!n->isLeaf()) { //if internal node
                if (p->isFull()) {
                    if (redistributeFrom == "left" && n == p->middle) {
                        n->addChild(p->left->right);
                        p->left->right = p->left->middle;
                        p->left->middle = 0;
                    } else if (redistributeFrom == "right" && n == p->middle) {
                        n->addChild(p->right->left);
                        p->right->left = p->right->middle;
                        p->right->middle = 0;
                    } else if (redistributeFrom == "middle" && n == p->left) {
                        n->addChild(p->middle->left);
                        p->middle->left = p->middle->middle;
                        p->middle->middle = 0;
                    } else if (redistributeFrom == "middle" && n == p->right) {
                        n->addChild(p->middle->right);
                        p->middle->right = p->middle->middle;
                        p->middle->middle = 0;          
                    }
                } else {
                    if (redistributeFrom == "right") {
                        n->addChild(p->right->left);
                        p->right->left = p->right->middle;
                        p->right->middle = 0;
                    } else {
                        n->addChild(p->left->right);
                        p->left->right = p->left->middle;
                        p->left->middle = 0;
                    }
                }
                
                
            }            

            redistributed = true;
        } 
        
        if (!redistributed) { //merge nodes
            Node * s;
            if (n->leftSibling()) { //merges tot he left
                if (n->leftSibling() == p->left) {
                    n->leftSibling()->addValue(p->small);
                    p->removeValue(p->small);
                } else if (n->leftSibling() == p->middle) {
                    p->middle->addValue(p->large);
                    p->removeValue(p->large);
                    p->right = p->middle;
                    p->middle = 0;
                }
 
                s = n->leftSibling();
            } else { //merges to the right
                if (n->rightSibling()) {
                    if (n->rightSibling() == p->middle) {
                        n->rightSibling()->addValue(p->small);
                        p->removeValue(p->small);
                        p->left = p->middle;
                        p->middle = 0;
                    } 
                }
                s = n->rightSibling();
            }
            if (!n->isLeaf()) { //transfers children if n is not a leaf
                s->transferChildren(n);    
            }
            if (n == p->right) {
                p->right = 0;
            } else if (n == p->middle) {
                p->middle = 0;
            } else if (n == p->left) {
                p->left = 0;
            }
            
            delete n;
            n = 0;
            
            if (p->empty()) {
                fix(p);
            }
        }
        
            
    }
    
}

bool Tree::search (const string & find) const { //returns boolean is search value is found in tree
    
    Node * cur = root;
    
    while (cur != 0) {
        if (cur->small == find || cur->large == find) {
            return true;
        } else if (find < cur->small) {
            cur = cur->left;
        } else if (!cur->large.empty() && find < cur->large) {
            cur = cur->middle;
        } else {
            cur = cur->right;
        }
    }
    
    return false;
}

Node * Tree::nodeSearch (const string & find) const { //returns node location of explicit parameter
    
    Node * cur = root;
    
    while (cur != 0) {
        if (cur->small == find || cur->large == find) {
            return cur;
        } else if (find < cur->small) {
            cur = cur->left;
        } else if (!cur->large.empty() && find < cur->large) {
            cur = cur->middle;
        } else {
            cur = cur->right;
        }
    }
    
    return cur;
}
