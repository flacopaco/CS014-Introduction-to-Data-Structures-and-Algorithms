#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
using namespace std;

#include "WordLadder.h"

WordLadder::WordLadder(const string & fileName) {
    
    ifstream inFS(fileName);
    string temp;
    
    if (!inFS.is_open()) {
        cout << "Error opening " << fileName << endl;
        return;
    }
    
    while(getline(inFS,temp)) {
        if (temp.size() != 5) {
            cout << "Non-5-letter-word found." << endl;
            return;
        }
        
        dict.push_back(temp);
    }
    
    inFS.close();
    
    // cout << dict.size() << endl;
    
    
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    
    if (!dictCheck(start) || !dictCheck(end)) {
        cout << "Non-5-letter-word passed in" << endl;
        return;
    }
    
    stack<string> startStack;
    queue<stack<string>> wordQueue;
    
    startStack.push(start);
    wordQueue.push(startStack);
    bool done = true;
    stack<string> finalLadder;
    
    while(!wordQueue.empty() && done) {
        
        string temp = wordQueue.front().top();
        list<string>::iterator itr;

        for (itr = dict.begin(); (itr != dict.end()) && done; ++itr) {
            int diff = letterDiffCounter(temp, *itr);
            
            if (diff == 1) {
                
                stack<string> tempStack;
                tempStack = wordQueue.front();
                tempStack.push(*itr);
                
                if (*itr == end) {
                    done = false;
                    finalLadder = tempStack;
                } else {
                    wordQueue.push(tempStack);
                    itr = dict.erase(itr);
                    --itr;
                }
            }
        }
        
        wordQueue.pop();
    }
    
    ofstream outFS(outputFile);
    if (start == end) {
        outFS << start;
    } else if (done) {
        outFS << "No Word Ladder Found.\n";
    } else {
        stack<string> reverseFinal;
        
        while (!finalLadder.empty()) {
            reverseFinal.push(finalLadder.top());
            finalLadder.pop();
        }
        
        while (!reverseFinal.empty()) {
            outFS << reverseFinal.top() << endl;
            reverseFinal.pop();
        }
    }
}

bool WordLadder::dictCheck(const string & compare) {
    
    list<string>::iterator itr;
    
    
    for (itr = dict.begin(); itr != dict.end(); ++itr) {
        if (compare == *itr) {
            return true;
        }
    }
    
    return false;
    
}

int WordLadder::letterDiffCounter(string start,string dictWord) {
    int counter = 0;
    
    for (unsigned i = 0; i < dictWord.size(); ++i) {
        if (start.at(i) != dictWord.at(i)) {
            ++counter;
        }
    }
    
    return counter;
}