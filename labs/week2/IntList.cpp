#include <string>
#include <iostream>
using namespace std;
#include "IntList.h"

IntList::IntList(){
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList(){
    
    while(!this->empty()){
        pop_front();
    }
    
}

void IntList::push_front(int value) {
    if(this->empty()) {
        IntNode* newNode = new IntNode(value);
        dummyHead->next = newNode;
        newNode->prev = dummyHead;
        newNode->next = dummyTail;
        dummyTail->prev = newNode;
        return;
    }
    IntNode* newNode = new IntNode(value);
    newNode->next = dummyHead->next;
    dummyHead->next = newNode;
    newNode->prev = dummyHead;
    newNode->next->prev = newNode;
    
}

void IntList::pop_front() {
    
    if (this->empty()) {
        return;
    }
    
    IntNode * temp = dummyHead->next;
    
    dummyHead->next = temp->next;
    dummyHead->next->prev = dummyHead;
    delete temp;
}

void IntList::push_back(int value) {
    if(this->empty()) {
        IntNode* newNode = new IntNode(value);
        dummyHead->next = newNode;
        newNode->prev = dummyHead;
        newNode->next = dummyTail;
        dummyTail->prev = newNode;
        return;
    }
    IntNode* newNode = new IntNode(value);
    newNode->prev = dummyTail->prev;
    dummyTail->prev = newNode;
    newNode->prev->next = newNode;
    newNode->next = dummyTail;
}
    
void IntList::pop_back(){
   
   if (this->empty()) {
        return;
    }
    
    IntNode * temp = dummyTail->prev;
    
    dummyTail->prev = temp->prev;
    dummyTail->prev->next = dummyTail;
    delete temp;

}

bool IntList::empty() const {
    if (dummyHead->next == dummyTail) {
        return true;
    } else {
        return false;
    }
}

void IntList::printReverse() const{
    IntNode* temp = dummyTail->prev;
    while(temp != dummyHead) {
        cout << temp->data;
        if (temp->prev != dummyHead) {
             cout << " ";
        }
        temp = temp->prev;
    }
}


ostream & operator <<(ostream &out, const IntList&rhs) {
    IntNode * temp = rhs.dummyHead->next;
    
    while (temp != rhs.dummyTail) {
        out << temp->data;
        if (temp->next != rhs.dummyTail) {
            out << " "; 
        }
        temp = temp->next;
    }
    
    return out;    
}




