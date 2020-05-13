#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s;
	hashTable = new list<WordEntry>[s];

}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    int hash = 0;
    int sSize;
    unsigned three = 3;
    if (s.size() < three) {
        sSize = s.size();
    } else {
        sSize = 3;
    }

    for (int i = 0; i < sSize; ++i) {
        int y = 3;
        for (int x = 0; x < i; ++x) {
            y = y * y;
        }
        
        char atI = s.at(i);
        
        hash += static_cast<int>(atI) * y;
        
    }
    
    return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    int sHash = computeHash(s);
    
    list<WordEntry>::iterator itr;

    for (itr = hashTable[sHash].begin(); (itr != hashTable[sHash].end()); ++itr) {
        if (itr->getWord() == s) {
            itr->addNewAppearance(score);
            return;
        }
    }
    
    WordEntry newEntry(s, score);
    hashTable[sHash].push_back(newEntry);
    return;
	 
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    cout << "size is " << size << endl;
    int sHash = computeHash(s);
    
    list<WordEntry>::iterator itr;

    for (itr = hashTable[sHash].begin(); (itr != hashTable[sHash].end()); ++itr) {
        if (itr->getWord() == s) {
            double average = itr->getAverage();
            return average;
        }
    }    
    
    return 2.0;

}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    
     int sHash = computeHash(s);
    
    list<WordEntry>::iterator itr;

    for (itr = hashTable[sHash].begin(); (itr != hashTable[sHash].end()); ++itr) {
        if (itr->getWord() == s) {
            return true;
        }
    }
    
    return false;

}

