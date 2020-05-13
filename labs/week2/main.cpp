#include <iostream>
#include <list>
using namespace std;

#include "IntList.h"

int main () {
    
    IntList testList;
    cout << testList << endl;
    testList.push_front(1);
    cout << testList << endl;
    testList.push_back(2);
    cout << testList << endl;
    testList.pop_front();
    cout << testList << endl;
    testList.pop_back();
    cout << testList << endl;
    testList.push_front(5);
    testList.push_back(6);
    testList.push_front(4);
    testList.push_back(7);
    cout << testList << endl;
    testList.printReverse();
    
    if (testList.empty()) {
        cout << endl << "True!" << endl;
    } else {
        cout << endl << "False!" << endl;
    }
    
    IntList testListTwo;
    if (testListTwo.empty()) {
        cout << endl << "True!" << endl;
    } else {
        cout << endl << "False!" << endl;
    }    
    return 0;
}