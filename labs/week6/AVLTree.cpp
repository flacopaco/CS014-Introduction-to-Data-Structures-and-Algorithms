#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "AVLTree.h"

AVLTree::AVLTree() {
	root = 0;
}

int AVLTree::height(Node* n) {
	if(n == 0)
		return -1;
    else
    	return height(n->left) > height(n->right) ? height(n->left) + 1: height(n->right) + 1;  
}

int AVLTree::balanceFactor(Node * curr) {
	return height(curr->left) - height(curr->right);
}

Node* AVLTree::findUnbalancedNode(Node* start) {

	
	if (!start) {
	    return 0;
	} else {
	    int balFac = abs(balanceFactor(start));
	    
	    if (balFac == 2) {
	        return start;
	    }
	} 
	return findUnbalancedNode(start->parent);
//     if(balancefactor == 2) {
//         if (start == root) {
//             cout << "returning root" << endl;
//         }
//     	return start;
//     }
// 	if(abs(balanceFactor(start->left)) > 2)
// 		return findUnbalancedNode(start->left);
// 	else
// 		return findUnbalancedNode(start->right);

}

void AVLTree::insert(const string & s) {
    if(root == 0) {
		root = new Node(s, 1);
	}
    else {
        Node* cur = root;
    	while(cur != 0) {
    		if(s < cur->item) {
    			if (cur->left == 0) {
    				Node *node = new Node(s, 1);
    				cur->left = node;
    				node->parent = cur;
    				Node * unbalancedNode = findUnbalancedNode(cur);
    				if (!unbalancedNode) {
    				    return;
    				} else {
    				    rotate(unbalancedNode);
    				    return;
    				}
           			cur = 0;
				}	
         		else 
         			cur = cur->left;	
			}
			else if(s == cur->item) {
				++(cur->count);
				cur = 0;
			}
      		else {
      			if (cur->right == 0) {
      				Node *node = new Node(s, 1);
      				cur->right = node;
      				node->parent = cur;
      				Node * unbalancedNode = findUnbalancedNode(cur);
    				if (!unbalancedNode) {
    				    return;
    				} else {
    				    rotate(unbalancedNode);
    				    return;
    				}      				
           			cur = 0;
				}
         		else
           			cur = cur->right;
			}
		}
        // int rootBalance = abs(balanceFactor(root));
        // if(rootBalance > 1) {
        //     cout << "root is out of balance, rebalancing" << endl;
        // 	Node* unbalancedNode = findUnbalancedNode(root);
        // 	rotate(unbalancedNode);
		//}
    }
}

void AVLTree::printBalanceFactors(Node * printNode) {
    if(printNode == 0)
		return;
	else {
		printBalanceFactors(printNode->left);
		cout << printNode->item << "(" << balanceFactor(printNode) << "), ";
		printBalanceFactors(printNode->right);
	}
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n) {
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->item <<" -> " <<n->left->item<<";"<<endl;    
        }
        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->item <<" -> " <<n->right->item<<";"<<endl;    
        }
    }
}

Node* AVLTree::rotateLeft(Node* cur) {

    // Node * b;
    // Node * c;
    
    // b = a->right;
    // c = b->right;
    
    // b->left = a;
    // a->right = c;
    // return b;
    if (cur->parent) {
        if (cur->parent->left == cur) { 
            cur->parent->left = cur->right;
        } else { 
            cur->parent->right = cur->right;
        }
    } else { 
        root = cur->right;
    }
        
    cur->right->parent = cur->parent;
    cur->parent = cur->right;
    Node * temp = cur->right->left;
    cur->right->left = cur;
    cur->right = temp;
    return cur->right;
}

Node* AVLTree::rotateRight(Node* cur) {
// 
    // Node * b;
    // Node * c;
    
    // b = d->left;
    // c = b->right;
    
    // b->right = d;
    // d->left = c;
    // return b;
    if (cur->parent) {
        if (cur->parent->left == cur) { 
            cur->parent->left = cur->left;
        } else { 
            cur->parent->right = cur->left;
        }
    } else { 
        root = cur->left;
    }
    
    cur->left->parent = cur->parent;
    cur->parent = cur->left;
    Node* temp = cur->left->right;
    cur->left->right = cur;
    cur->left = temp;
    return cur->left;
}

void AVLTree::rotate(Node* &start) {
    Node * newSub;
    int startBalance = balanceFactor(start);
    if(startBalance == 2 && balanceFactor(start->left) == 1) {

    	newSub = rotateRight(start);
    	if (root == start) {
    	    root = newSub;
    	}
	}  
    else if(startBalance == 2 && balanceFactor(start->left) == -1) {

        rotateLeft(start->left);
        newSub = rotateRight(start);
        if (root == start) {
            root = newSub;
        }
    }
    else if(startBalance == -2 && balanceFactor(start->right) == -1) {
    	newSub = rotateLeft(start);
    	if (root == start) {
    	    root = newSub;
    	}
	}
    else if(startBalance == -2 && balanceFactor(start->right) == 1) {

        rotateRight(start->right);  
    	newSub = rotateLeft(start); 
    	if (root == start) {
    	    root = newSub;
    	}
    }
}