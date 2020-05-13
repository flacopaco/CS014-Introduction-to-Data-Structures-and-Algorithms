#include <iostream>
#include <string>
#include <algorithm>
#include "BSTree.h"
#include "Node.h"

using namespace std;

BSTree::~BSTree() { //destructor
    Node * curr = root;
    while (root != 0) {
        string words = curr->words;
        remove(words);
    }
}

/*void BSTree::destructorTraverse(Node* root) { //doesnt work 
    if(root == 0) {
        return;
    }
    destructorTraverse(root->left); //recursive call for deleting the left
    destructorTraverse(root->right); //recursive call for deleting the right
    delete root; //clears the root
}
*/


void BSTree::insert(const string & userString) {
    if (root == 0) {
        root = new Node(userString);
        return;
    } else {
        Node * curr = root;
        
        while (curr != 0) {
            if (userString < curr->words) { //checks if it is on the left side
                if (curr->left == 0) {
                    curr->left = new Node(userString);
                    return;
                } else {
                    curr = curr->left;
                }
            } else if (userString > curr->words) { //checks if it is on the right side
                if (curr->right == 0) {
                    curr->right = new Node(userString);
                    return;
                } else {
                    curr = curr->right;
                }
            } else if (userString == curr->words) { //checks if it is the same word
                curr->count += 1;
                return;
            }
            
        }
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

bool BSTree::search(const string & toFind) const { //returns boolean if the value exists in the tree
    
    Node * curr = root;
    
    if (curr != 0) {
        if (curr->words == toFind) {
            return true;
        } else if (curr->words > toFind) {
            return search(curr->left, toFind);
        } else {
            return search(curr->right, toFind);
        }
    }
    return false;
}

bool BSTree::search(Node * curr, const string & toFind) const { //private helper recursive function to search
    if (curr != 0) {
        if (curr->words == toFind) {
            return true;
        } else if (curr->words > toFind) {
            return search(curr->left, toFind);
        } else {
            return search(curr->right, toFind);
        }
    }
    return false;
}

string BSTree::largest() const { //finds right most node
    if (root == 0) {
        return "";
    }
    
    Node * curr = root;
    
    while (curr != 0) {
        if (curr->right == 0) {
            return curr->words;
        } else {
            curr = curr->right;
        }
    }
    return "";
}

string BSTree::smallest() const { //finds left most node
    if (root == 0) {
        return "";
    }
    
    Node * curr = root;
    
    while (curr != 0) {
        if (curr->left == 0) {
            return curr->words;
        } else {
            curr = curr->left;
        }
    }
    return "";
}

int BSTree::height(const string & toFindHeight) const { //height - max number of edges to leaf
    int counter = 0;
    Node * curr = root;
    
    while (curr != 0) {
        if (curr->words == toFindHeight) {
            return heightHelper(curr, counter);
        } else if (curr->words < toFindHeight) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return -1;
}

int BSTree::heightHelper(Node * curr, int & counter) const {
    if (curr == 0) {
        return counter;
    }
    if (curr->right == 0 && curr->left == 0) {
        return counter;
    } 
    counter = counter + 1;
    int counterCopy1 = counter;
    int counterCopy2 = counter;
    
    counterCopy1 = heightHelper(curr->right, counterCopy1); //splits to check right and left nodes
    counterCopy2 = heightHelper(curr->left, counterCopy2);
    
    if (counterCopy1 > counterCopy2) {
        return counterCopy1;
    } else if (counterCopy1 < counterCopy2) {
        return counterCopy2;
    }
    return counterCopy1;
}

void BSTree::remove(const string & sentence) { 
    if (!search(sentence)) {
        return;
    }
    
    Node * parent = 0;
    Node * curr = root;
    
    if (curr->words == sentence) {
        if (curr->count > 1) {
            --curr->count;
            return;
        } else {
            remove(curr, parent, sentence); //calls recursive helper function
            return;
        }
         
    } else if (curr->words > sentence) {
        parent = curr;
        curr = curr->left;
        remove(curr, parent, sentence);
    } else {
        parent = curr;
        curr = curr->right;
        remove(curr, parent, sentence);
    }
    return;
}



void BSTree::remove(Node * curr, Node * parent, const string & sentence) {
    if (curr->words == sentence) {
        if (curr->count > 1) {
            --curr->count;
            return;
        } else if (curr->left == 0 && curr->right == 0) { //if leaf exists
            if (parent != 0) { //disconnects leaf from parent
                if (curr == parent->right) {
                    parent->right = 0;
                } else {
                    parent->left = 0;
                }
            }else if (root == curr) { //if there is a leaf and root, implies only one left
                root = 0;
            }
            delete curr;
            curr = 0;
            return;
        } else if (curr->left) { //if the left exists find max in left
            string leftMax = findMax(curr->left);
            int leftMaxCount = countFinder(curr->left, leftMax);
            curr->words = leftMax;
            curr->count = leftMaxCount;
            while (countFinder(curr->left, leftMax) != 0) {
                remove(curr->left, curr, leftMax);
            }
            
        } else {
            string rightMin = findMin(curr->right);
            int rightMinCount = countFinder(curr->right, rightMin);
            curr->words = rightMin;
            curr->count = rightMinCount;
            while (countFinder(curr->right, rightMin) != 0) {
                remove(curr->right, curr, rightMin);
            }
        }
    } else if (curr->words > sentence) {
        parent = curr;
        curr = curr->left;
        remove(curr, parent, sentence);
        
    } else {
        parent = curr;
        curr = curr->right;
        remove(curr, parent, sentence);
    }
}

string BSTree::findMax(Node * start) const {
    Node * curr = start;
    
    while (curr != 0) {
        if (curr->right == 0) {
            return curr->words;
        } else {
            curr = curr->right;
        }
    }
    
    return curr->words;

}

string BSTree::findMin(Node * start) const {
    Node * curr = start;
    
    while (curr != 0) {
        if (curr->left == 0) {
            return curr->words;
        } else {
            curr = curr->left;
        }
    }
    return curr->words;
}


int BSTree::countFinder(Node * curr, const string & toFind) const { //recursively finds the count
    if (curr != 0) {
        if (curr->words == toFind) {
            return curr->count;
        } else if (curr->words > toFind) {
            return countFinder(curr->left, toFind);
        } else {
            return countFinder(curr->right, toFind);
        }
    }
    return 0;
}


