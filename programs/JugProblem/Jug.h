#ifndef JUG_H
#define JUG_H

#include <vector>
#include <stack>
#include <list>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <sstream>
using namespace std;

/*uses vertex based off of lab 9's vertices, priorityQueue implemented
with STL list, STL stack, and vectors
*/



class Vertex {
public:
  vector<int> neighbors;
  pair<int, int> label;
  int distance;
  Vertex* prev;
  bool edges;
  
  Vertex():neighbors(6, INT_MAX),label(0,0),distance(INT_MAX),prev(0), edges(false) {}
  int getPriority() const;
  ~Vertex(){}
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        vector<Vertex> vertices;
        int goal;
        int maxA;
        int maxB;
        int costFillA;
        int costFillB;
        int costEmptyA;
        int costEmptyB;
        int costAtoB;
        int costBtoA;
        int findPairIndex(pair <int, int>);
        void relax(Vertex *, Vertex *, int);
        void intializeSource(Vertex * s);
        void dijkstra(Vertex *);
        void assignSolution(stringstream &, Vertex *);
        //anything else you need
};


class priorityQueue { //uses list implementation keeping lowest priority at front
    private:
      list<Vertex *> priorityList;      
     
    public:
      //default empty constructor
      priorityQueue();
    
      void enqueue ( Vertex * ); //places at front if has lowest priority, else pushes back
    
      void dequeue ( ); //pops front 
    
      /*Returns the Vertex with highest priority by returning front*/
      Vertex* lowest ( ); 
      
      bool empty() const; //returns true if empty else false
      
      void fix(); //makes sure lowest priority is at the front

};




#endif