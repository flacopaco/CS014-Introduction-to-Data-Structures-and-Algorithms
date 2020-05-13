#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap() : numItems(0) {}

void Heap::enqueue(PrintJob* item) {
    if (numItems < MAX_HEAP_SIZE) {
        if (numItems == 0) {
            arr[numItems] = item;
            ++numItems;
        }
        else {
            int x = numItems;
            while (x > 0 && arr[(x-1)/2]->getPriority() < item->getPriority()) {
                arr[x] = arr[(x-1)/2];
                x = (x-1)/2;
            }
            arr[x] = item;
            ++numItems;
        }
    }
}

void Heap::dequeue() {
    if (numItems == 0) {
        return;
    }
    if (numItems == 1) {
        arr[0] = 0;
        --numItems;
        return;
    }
    arr[0] = arr[numItems-1];
    arr[numItems-1] = 0;
    --numItems;
    if (numItems <= 2) {
        if (numItems == 1) {
            return;
        }
        if (arr[0]->getPriority() < arr[1]->getPriority()) {
            PrintJob* temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return;
    }
    if (arr[0]->getPriority() < arr[1]->getPriority() || arr[0]->getPriority() < arr[2]->getPriority()) {
        trickleDown(0);
    }
}

PrintJob* Heap::highest() {
    if (numItems == 0) {
        return 0;
    }
    return arr[0];
}

void Heap::print() {
    if (numItems == 0) {
        return;
    }
    cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages();
    cout << endl;
 /*   Priority: priority, Job Number: jobNum, Number of Pages: numPages
  (Add a new line at the end.) */

}

void Heap::trickleDown(int num) {
    int x = num;
    int left = 2*x+1;
    int right = 2*x+2;
    
    if (left < numItems && right < numItems) {
        if (arr[x]->getPriority() < arr[left]->getPriority() || arr[x]->getPriority() < arr[right]->getPriority()) {
            
            if (arr[left]->getPriority() > arr[right]->getPriority()) { // trickle left
                PrintJob* temp = arr[x];    
                arr[x] = arr[left];
                arr[left] = temp;
                x = left;
                left = 2*x+1;
                right = 2*x+2;
                if (right < numItems) {
                    trickleDown(x);
                }
            }
            else { //trickle right
                PrintJob* temp = arr[x];
                arr[x] = arr[right];
                arr[right] = temp;
                x = right;
                left = 2*x+1;
                right = 2*x+2;
                if (right < numItems) {
                    trickleDown(x);
                }
            }
        }
    }
    else if (left < numItems && right >= numItems) {
        if (arr[left]->getPriority() > arr[x]->getPriority()) {
            PrintJob* temp = arr[x];
            arr[x] = arr[left];
            arr[left] = temp;
            x = left;
        }
    }
}
