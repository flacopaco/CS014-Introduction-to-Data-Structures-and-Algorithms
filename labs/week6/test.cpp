#include <iostream>
using namespace std;
#include "BSTree.h"

int main() {
    
    BSTree testTree;
    string s1 = "dog";
    string s2 = "cat";
    string s3 = "cow";
    string s4 = "doggo";
    string s5 = "catty";
    string s6 = "cows";
    string s7 = "dog";
    string s8 = "cat";
    string s9 = "cow";
    cout << "strings made" << endl;
    
    testTree.insert(s1);
    cout << "inserted" << endl;
    testTree.insert(s2);
    testTree.insert(s3);
    testTree.insert(s4);
    cout << "inserted" << endl;
    testTree.insert(s5);
    testTree.insert(s6);
    testTree.insert(s7);
    cout << "inserted" << endl;
    testTree.insert(s8);
    testTree.insert(s9);
    cout << "inOrder: ";
    testTree.inOrder();
    cout << endl;
    cout << "preOrder: ";
    testTree.preOrder();
    cout << endl;
    cout << "postOrder: ";
    testTree.postOrder();
    cout << endl;

    cout << endl;
    if (testTree.search("dog")) {
        cout << "found dog" << endl;
    }
    if (!testTree.search("doggy")) {
        cout << "did not find doggy" << endl;
    }
    
    cout << testTree.smallest() << endl;
    cout << testTree.largest() << endl;
    cout << "dog's height (the root) is: " << testTree.height("dog") << endl;
    cout << "doggo's height is: " << testTree.height("doggo") << endl;
    cout << "cow's height is: " << testTree.height("cow") << endl;
    testTree.remove("catty");
    cout << "catty removed" << endl;
    cout << "searching for catty" << endl;
    if (!testTree.search("catty")) {
        cout << "catty successfully removed" << endl;
    }
    testTree.inOrder();
    cout << endl;
    testTree.remove("dog");
    cout << "dog removed" << endl;
    cout << "searching for dog" << endl;
    if (!testTree.search("dog")) {
        cout << "dog successfully removed" << endl;
    }
    testTree.inOrder();
    cout << endl;

    
    return 0;
}
