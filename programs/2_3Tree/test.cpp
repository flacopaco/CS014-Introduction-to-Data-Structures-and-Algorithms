#include <iostream>
using namespace std;

#include "Tree.h"
#include "Node.h"

int main() {
    
    // Tree testTree;
    
    // testTree.insert("C");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("O");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("G");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("K");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("P");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("N");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("E");
    // testTree.inOrder();
    // cout << endl << endl;
    // testTree.insert("I");
    // testTree.inOrder();
    // cout << endl << endl;
    
    Tree testTree2;
    testTree2.insert("C");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("C");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("C");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("O");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("O");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("O");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("G");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("G");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("G");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("C");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("C");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("O");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("O");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("K");
    testTree2.inOrder();
    cout << endl;
    testTree2.remove("K");
    testTree2.inOrder();
    cout << endl;
    testTree2.insert("K");
    testTree2.inOrder();
    cout << endl;
    
    
    
}