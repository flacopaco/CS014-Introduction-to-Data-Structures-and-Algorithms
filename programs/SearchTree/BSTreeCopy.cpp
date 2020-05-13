#include <iostream>
using namespace std;

#include "BSTree.h"
#include "Node.h"

void BSTree::insert(const string & userString) {
    if (root == 0) {
        root = new Node(userString);
        return;
    } else {
        Node * curNode = root;
        
        while (curNode != 0) {
            if (userString < curNode->words) { //checks if on left side
                if (curNode->left == 0) {
                    curNode->left = new Node(userString);
                    return;
                } else {
                    curNode = curNode->left;
                }
            } else if (userString > curNode->words) { //checks if on right side
                if (curNode->right == 0) {
                    curNode->right = new Node(userString);
                    return;
                } else {
                    curNode = curNode->right;
                }
            } else if (userString == curNode->words) { //checks if same word
                curNode->count += 1;
                return;
            }
            
        }
    }
}

bool BSTree::search(const string & toFind) const { //returns boolean if value exists in BST
    
    Node * cur = root;
    
    if (cur != 0) {
        if (cur->words == toFind) {
            return true;
        } else if (cur->words > toFind) {
            return search(cur->left, toFind);
        } else {
            return search(cur->right, toFind);
        }
        
    }
    
    return false;
}

bool BSTree::search(Node * cur, const string & toFind) const { //private helper recursive
    
    if (cur != 0) {
        if (cur->words == toFind) {
            return true;
        } else if (cur->words > toFind) {
            return search(cur->left, toFind);
        } else {
            return search(cur->right, toFind);
        }
        
    }
    
    return false;
}

void BSTree::inOrder() const { //prints in ascending order
    if (root == 0) {

        return;
    }
    
    inOrder(root);
}

void BSTree::inOrder(Node * printNode) const {
    if (printNode) {
        inOrder(printNode->left);
        cout << printNode->words << "(" << printNode->count << "), ";
        inOrder(printNode->right);
    }
    
}

void BSTree::preOrder() const { //root, left, right
    if (root == 0) {
        return;
    }
    
    preOrder(root);
}

void BSTree::preOrder(Node * printNode) const {
    if (printNode) {
        cout << printNode->words << "(" << printNode->count << "), ";
        preOrder(printNode->left);
        preOrder(printNode->right);
    }
    
}

void BSTree::postOrder() const { //left, right, root
    if (root == 0) {
        return;
    }
    
    postOrder(root);
}

void BSTree::postOrder(Node * printNode) const {
    if (printNode) {
        postOrder(printNode->left);
        postOrder(printNode->right);
        cout << printNode->words << "(" << printNode->count << "), ";
    }
    
}

string BSTree::largest() const { //finds right most node
    if (root == 0) {
        return "";
    }
    
    Node * cur = root;
    
    while (cur != 0) {
        if (cur->right == 0) {
            return cur->words;
        } else {
            cur = cur->right;
        }
    }
    
    return "";
}

string BSTree::smallest() const { //finds left most node
    if (root == 0) {
        return "";
    }
    
    Node * cur = root;
    
    while (cur != 0) {
        if (cur->left == 0) {
            return cur->words;
        } else {
            cur = cur->left;
        }
    }
    
    return "";
}

int BSTree::height(const string & toFindHeight) const { //height - max number of edges to external
    int counter = 0;
    Node * cur = root;
    
    while (cur != 0) {
        if (cur->words == toFindHeight) {
            return heightHelp(cur, counter);
                
            
        } else if (cur->words < toFindHeight) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    
    return -1;
}

int BSTree::heightHelp(Node * cur, int & counter) const {

    if (cur == 0) {
        return counter;
    }
    
    if (cur->right == 0 && cur->left == 0) {
        return counter;
    } 
    
    ++counter;
    int counterCopy1 = counter;
    int counterCopy2 = counter;
    
    counterCopy1 = heightHelp(cur->right, counterCopy1); //splits to check right and left
    counterCopy2 = heightHelp(cur->left, counterCopy2);
    
    if (counterCopy1 > counterCopy2) {
        return counterCopy1;
    } else if (counterCopy1 < counterCopy2) {
        return counterCopy2;
    }
    
    return counterCopy1;
    
}

void BSTree::remove(const string & toRemove) { //removes node with slide algorithm
    if (!search(toRemove)) return;
    Node * par = 0;
    remove(root, par, toRemove);
}

void BSTree::remove(Node * cur, Node * par, const string & toRemove) {
    cout << "remove called" << endl;
    cout << "checking " << toRemove << " vs " << cur->words << endl;
    if (cur->words == toRemove) {
        cout << "found to remove" << endl;
        if (cur->count > 1) {
            --cur->count;
            return;            
            } else if (cur->right == 0 && cur->left == 0) {
                cout << "is a leaf" << endl;
                if (par != 0) { //disconnects external from parent
                cout << "that has parents" << endl;
                    if (cur == par->right) {
                        cout << "disconnecting from parents right" << endl;
                        par->right = 0;
                    } else {
                        cout << "disconnecting from parents left" << endl;
                        par->left = 0;
                    }
                } else if (root == cur) {
                    root = 0;
                }
                cout << "let's delete this" << endl;
                delete cur;
                
                cout << cur->words << endl;
                
                return;
            } else if (cur->left) {
                Node * leftMaxNode = findMax(cur->left);
                leftMaxNode->right = cur->right;
                leftMaxNode->left = cur->left;
                cur = leftMaxNode;
                string replacement = cur->words;
                remove(cur->left, cur, replacement);
                return;
            } else {
                Node * rightMinNode = findMin(cur->right);
                rightMinNode->right = cur->right;
                rightMinNode->left = cur->left;
                cur = rightMinNode;
                string replacement = cur->words;
                remove(cur->right, cur, replacement);
                return;
            }
    } else if (cur->words > toRemove) {
        cur = cur->left;
        par = cur;
        remove(cur, par, toRemove);
    } else {
        cur = cur->right;
        par = cur;
        remove(cur, par, toRemove);
    }
}

Node * BSTree::findMax(Node * start) const {
    Node * cur = start;
    while (cur != 0) {
        if (cur->right == 0) {
            Node * newNode = new Node(*cur);
            return newNode;
        } else {
            cur = cur->right;
        }
    }
    return cur;

}

Node * BSTree::findMin(Node * start) const {
    Node * cur = start;
    while (cur != 0) {
        if (cur->left == 0) {
            Node * newNode = new Node(*cur);
            return newNode;
        } else {
            cur = cur->left;
        }
    }
    return cur;
}


BSTree::~BSTree() { //desctructor
    cout << "   destructor called" << endl;

    Node * cur = root;
    while (root != 0) {

        string words = cur->words;
        remove(words);
        
        
    }
}

