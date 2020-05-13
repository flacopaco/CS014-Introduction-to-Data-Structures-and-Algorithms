#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    
    unsigned returnIndex = index;
    for(unsigned i=index; i<vals.size(); ++i){
        if(vals.at(i) < vals.at(returnIndex)){
            returnIndex = i;
        }
       
    }
    return returnIndex;
}

//Passes in an index of type int and a vector of type T (T could be string, double or int). The function returns the index of the min value starting from "index" to the end of the "vector".
template<typename T>
void selection_sort(vector<T> &vals){
     for(unsigned i=0; i<vals.size(); ++i){
          int minimumIndex = min_index(vals,i);
          swap(vals.at(i), vals.at(minimumIndex));
          
   }
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template <typename T>
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

    


//Passes in a vector of type T and sorts them based on the selection sort method. This function should utilize the min_index function to find the index of the min value in the unsorted portion of the vector.

int main(){
    
    vector<int> val;
    val.push_back(2);
    val.push_back(3);
    val.push_back(7);
    val.push_back(4);
    val.push_back(1);
    

    cout << "Unsorted vector: ";
    for(unsigned i=0; i<val.size();++i){
        cout << val.at(i) << " ";
    }
    
    cout << endl;
    cout <<"Min index: " << min_index(val, 0) << endl;

    
    selection_sort(val);
    cout << "Sorted vector: ";
    for(unsigned i=0; i<val.size();++i){
        cout << val.at(i) << " ";
    }    
    
    vector<string> names;
    names.push_back("daniel");
    names.push_back("brian");
    names.push_back("bailey");
    names.push_back("thomas");
    names.push_back("andrew");
    
     cout << endl;
     
    cout << "Unsorted vector: ";
    for(unsigned i=0; i<names.size();++i){
        cout << names.at(i) << " ";
    }
    
    cout << endl;
    cout <<"Min index: " << min_index(names, 0) << endl;

    
    selection_sort(names);
    cout << "Sorted vector: ";
    for(unsigned i=0; i<names.size();++i){
        cout << names.at(i) << " ";
    } 
    cout << endl;
    


    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     
     cout << "Size: " << vals.size() << endl;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         try {
            curChar = getElement(vals,index);
         }
         
            catch (const std::out_of_range& excpt) {
            cout << "out of range exception occured" << endl;
                 
             }
    
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}