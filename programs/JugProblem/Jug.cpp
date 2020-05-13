#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <sstream>
using namespace std;

#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    goal = N;
    maxA = Ca;
    maxB = Cb;
    costFillA = cfA;
    costFillB = cfB;
    costEmptyA = ceA;
    costEmptyB = ceB;
    costAtoB = cpAB;
    costBtoA = cpBA;
    
    if (goal < 1 || maxA < 1 || maxB < 1 || costFillA < 1 || costFillB < 1 || costEmptyA < 1 || costEmptyB < 1 || costAtoB < 1 || costBtoA < 1) {
        return;
        
    }

    Vertex v;
    pair<int, int> intialJugs(0 ,0);
    v.label = intialJugs;
    
    vertices.push_back(v);
    bool done = false;

    while (done != true) {

        unsigned size = vertices.size();

        
        for (unsigned i = 0; i < size; ++i) {
            if (!vertices.at(i).edges) { //if vertex does not have all neighbors assigned
                if (vertices.at(i).neighbors.at(0) == INT_MAX) { //checks if index of fillA edge is assigned
                    if (vertices.at(i).label.first == maxA) {
                        vertices.at(i).neighbors.at(0) = i;
                    } else {
                        pair<int, int> filledA (maxA, vertices.at(i).label.second);

                        int edgeIndex = findPairIndex(filledA);
                        if (edgeIndex != -1) {
                            vertices.at(i).neighbors.at(0) = edgeIndex;
                        } else {
                            Vertex filledVertex;
                            filledVertex.label = filledA;
                            vertices.push_back(filledVertex);
                            vertices.at(i).neighbors.at(0) = vertices.size() - 1;
                        }
                    }
                }
                
                if (vertices.at(i).neighbors.at(1) == INT_MAX) { //checks if index of fillB edge is assigned
                    if (vertices.at(i).label.second == maxB) {
                        vertices.at(i).neighbors.at(1) = i;
                    } else {
                        pair<int, int> filledB (vertices.at(i).label.first, maxB);
                        int edgeIndex = findPairIndex(filledB);
                        
                        if (edgeIndex != -1) {
                            vertices.at(i).neighbors.at(1) = edgeIndex;
                        } else {
                            Vertex filledVertex;
                            filledVertex.label = filledB;
                            vertices.push_back(filledVertex);
                            vertices.at(i).neighbors.at(1) = vertices.size() - 1;
                        }
                    }
                }
                
                if (vertices.at(i).neighbors.at(2) == INT_MAX) { //checks if index of emptyA edge is assigned
                    if (vertices.at(i).label.first == 0) {
                        vertices.at(i).neighbors.at(2) = i;
                    } else {
                        pair<int, int> emptyA (0, vertices.at(i).label.second);
                        int edgeIndex = findPairIndex(emptyA);
                        
                        if (edgeIndex != -1) {
                            vertices.at(i).neighbors.at(2) = edgeIndex;
                        } else {
                            Vertex emptiedA;
                            emptiedA.label = emptyA;
                            vertices.push_back(emptiedA);
                            vertices.at(i).neighbors.at(2) = vertices.size() - 1;
                        }
                    }
                    
                }
                
                if (vertices.at(i).neighbors.at(3) == INT_MAX) { //checks if index of emptyB edge is assigned 
                    if (vertices.at(i).label.second == 0) {
                        vertices.at(i).neighbors.at(3) = i;
                    } else {
                        pair<int, int> emptyB (vertices.at(i).label.first, 0);
                        int edgeIndex = findPairIndex(emptyB);
                        
                        if (edgeIndex != -1) {
                            vertices.at(i).neighbors.at(3) = edgeIndex;
                        } else {
                            Vertex emptiedB;
                            emptiedB.label = emptyB;
                            vertices.push_back(emptiedB);
                            vertices.at(i).neighbors.at(3) = vertices.size() - 1;
                        }
                    }
                    
                }
                
                if (vertices.at(i).neighbors.at(4) == INT_MAX) { //cheecks if index of pourAtoB edge is assigned
                    if (vertices.at(i).label.second == maxB || vertices.at(i).label.first == 0) {
                        vertices.at(i).neighbors.at(4) = i;
                    } else {
                        int volumeA = vertices.at(i).label.first;
                        int volumeB = vertices.at(i).label.second;
                        if (volumeB + volumeA <= maxB) {
                            pair<int, int> jugAtoB (0, volumeB + volumeA);
                            int edgeIndex = findPairIndex(jugAtoB);
                            
                            if (edgeIndex != -1) {
                                vertices.at(i).neighbors.at(4) = edgeIndex;
                            } else {
                                Vertex aPouredB;
                                aPouredB.label = jugAtoB;
                                vertices.push_back(aPouredB);
                                vertices.at(i).neighbors.at(4) = vertices.size() - 1;
                            }
                        } else {
                            int newA = volumeA - (maxB - volumeB);
                            int newB = maxB;
                            pair<int, int> jugAtoB (newA, newB);
                            int edgeIndex = findPairIndex(jugAtoB);
                            
                            if (edgeIndex != -1) {
                                vertices.at(i).neighbors.at(4) = edgeIndex;
                            } else {
                                Vertex aPouredB;
                                aPouredB.label = jugAtoB;
                                vertices.push_back(aPouredB);
                                vertices.at(i).neighbors.at(4) = vertices.size() - 1;
                            }
                        }
  
                    }
                    
                }

                if (vertices.at(i).neighbors.at(5) == INT_MAX) { //checks if index of BtoA edge is assigned
                    if (vertices.at(i).label.first == maxA || vertices.at(i).label.second == 0) {
                        vertices.at(i).neighbors.at(5) = i;
                    } else {
                        int volumeA = vertices.at(i).label.first;
                        int volumeB = vertices.at(i).label.second;
                        if (volumeB + volumeA <= maxA) {
                            pair<int, int> jugBtoA (volumeB + volumeA, 0);
                            int edgeIndex = findPairIndex(jugBtoA);
                            
                            if (edgeIndex != -1) {
                                vertices.at(i).neighbors.at(5) = edgeIndex;
                            } else {
                                Vertex bPouredA;
                                bPouredA.label = jugBtoA;
                                vertices.push_back(bPouredA);
                                vertices.at(i).neighbors.at(5) = vertices.size() - 1;
                            }
                        
                        } else {
                            int newA = maxA;
                            int newB = volumeB - (maxA - volumeA);
                            pair<int, int> jugBtoA (newA, newB);
                            int edgeIndex = findPairIndex(jugBtoA);
                            
                            if (edgeIndex != -1) {
                                vertices.at(i).neighbors.at(5) = edgeIndex;
                            } else {
                                Vertex bPouredA;
                                bPouredA.label = jugBtoA;
                                vertices.push_back(bPouredA);
                                vertices.at(i).neighbors.at(5) = vertices.size() - 1;
                            }
                        }
                    }
                    
                }
                
                vertices.at(i).edges = true;
            }
        }
        
        unsigned fullNeighbors = 0;
        
        for (unsigned x = 0; x < vertices.size(); ++x) {
            if (vertices.at(x).edges) {
                ++fullNeighbors;
            }
        }
        
        if (fullNeighbors == vertices.size()) {
            done = true;

        }
    }

}

Jug::~Jug() { //destructor
    while (vertices.size() != 0) {
        vertices.pop_back();
    }
}

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.

int Jug::solve(string & solution) {
    if (goal < 1 || maxA < 1 || maxB < 1 || costFillA < 1 || costFillB < 1 || costEmptyA < 1 || costEmptyB < 1 || costAtoB < 1 || costBtoA < 1) {
        solution = "";
        return -1;
    }
    //0 < Ca ≤ Cb and N ≤ Cb ≤ 1000
    if (maxA > maxB || goal > maxB || maxB > 1000 || goal > 1000)  {
        solution = "";
        return -1;
    }
    
    stringstream SS;
    
    Vertex * s = &vertices.at(0);
    dijkstra(s);
    for (unsigned i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i).label.second == goal && vertices.at(i).label.first == 0) {
            assignSolution(SS, &vertices.at(i));
            solution = SS.str();
            return 1;
        }
    }
    
    solution = "";
    return 0;
     
}

void Jug::intializeSource(Vertex * start) { //intializes start of dijkstras at 0,0
    start->distance = 0;
}

void Jug::dijkstra(Vertex * start) { //runs dijkstra's algorithm to find shortest paths
    intializeSource(start);
    vector<Vertex> cloud;
    priorityQueue priorQueue;
    for (unsigned i = 0; i < vertices.size(); ++i) {
        priorQueue.enqueue(&vertices.at(i));
    }
    
    Vertex * u;
    
    while (!priorQueue.empty()) {
        u = priorQueue.lowest();

        priorQueue.dequeue();
        cloud.push_back(*u);
        for (unsigned x = 0; x < u->neighbors.size(); ++x) {
            int relaxCost;
            if (x == 0) {
                relaxCost = costFillA;
            } else if (x == 1) {
                relaxCost = costFillB;
            } else if (x == 2) {
                relaxCost = costEmptyA;
            } else if (x == 3) {
                relaxCost = costEmptyB;
            } else if (x == 4) {
                relaxCost = costAtoB;
            } else if (x == 5) {
                relaxCost = costBtoA;
            }
            relax(u, &vertices.at(u->neighbors.at(x)), relaxCost);
            
            priorQueue.fix();
        }
    }
}

void Jug::assignSolution(stringstream & solution, Vertex * current) { //assigns steps to solution in string
    Vertex * previous = current->prev;
    Vertex * cur = current;
    stack<string> solutionStack;
    
    stringstream success;
    success << "success " << current->distance;
    solutionStack.push(success.str());
    
    while (cur != 0 && previous != 0) {
        if (cur->label == vertices.at(previous->neighbors.at(0)).label) {
            solutionStack.push("fill A");
        } else if (cur->label == vertices.at(previous->neighbors.at(1)).label) {
            solutionStack.push("fill B");
        } else if (cur->label == vertices.at(previous->neighbors.at(2)).label) {
            solutionStack.push("empty A");
        } else if (cur->label == vertices.at(previous->neighbors.at(3)).label) {
            solutionStack.push("empty B");
        } else if (cur->label == vertices.at(previous->neighbors.at(4)).label) {
            solutionStack.push("pour A B");
        } else if (cur->label == vertices.at(previous->neighbors.at(5)).label) {
            solutionStack.push("pour B A");
        }
        
        cur = previous;
        if (cur != 0) {
            previous = cur->prev;
        }
    }
    
    
    while (!solutionStack.empty()) {
        solution << solutionStack.top();
        solutionStack.pop();
        if (!solutionStack.empty()) {
            solution << endl;
        }        
    }
    
    
}



void Jug::relax(Vertex *u, Vertex *v, int weight) { //relaxes if possible by assigning lower weight
    if (v->distance > u->distance + weight) {
        v->distance = u->distance + weight;
        v->prev = u;
    }
}

int Jug::findPairIndex(pair <int, int> compare) { //either returns index of given pair or -1 if not found
    for (unsigned i = 0; i < vertices.size(); ++i) {
        if (compare == vertices.at(i).label) {
            return i;
        }
    }
    
    return -1;
}




priorityQueue::priorityQueue() {} //empty priorQueue

void priorityQueue::enqueue(Vertex * item) {
    if (priorityList.size() == 0) {
        priorityList.push_back(item); // empty
    }
    
    if (item->distance < priorityList.front()->distance) {
        priorityList.push_front(item);
    } else {
        priorityList.push_back(item);
    }
}

void priorityQueue::fix() { //makes sure highest/lowest priority is at the front if contents changed (such as by djikstras)
    list<Vertex *>::iterator itr;
    for (itr = priorityList.begin(); itr != priorityList.end(); ++itr) {
        Vertex * front = priorityList.front();
        if ((*itr)->getPriority() < front->getPriority()) {
            Vertex * v = *itr;
            itr = priorityList.erase(itr);
            priorityList.push_front(v);
        }
    }
}

void priorityQueue::dequeue() {
   priorityList.pop_front();
    
}

Vertex * priorityQueue::lowest() {

    return priorityList.front();
}



bool priorityQueue::empty() const {
    return priorityList.empty();
}

int Vertex::getPriority() const {
    return distance;
}
