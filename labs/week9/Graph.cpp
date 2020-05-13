#include <iostream>
#include <stack>
using namespace std;

#include "Graph.h"
#include "Vertex.h"

Graph::Graph() {

}

Graph::Graph(ifstream & ifs) {
    int numVertices;
    int numEdges;
    
    ifs >> numVertices;
    ifs.ignore();
    ifs >> numEdges;
    ifs.ignore();
    
 
    string vertexName;
    
    for (int i = 0; i < numVertices; ++i) {
        Vertex v;
        getline(ifs, vertexName);
        
        v.label = vertexName;
        vertices.push_back(v);   
    }
    
    for (int x = 0; x < numEdges; ++x) {
        string startVertex;
        string endVertex;
        int edgeWeight;
        int startIndex;
        int endIndex;
        
        ifs >> startVertex;
        ifs >> endVertex;
        ifs >> edgeWeight;
        
        for (unsigned j = 0; j < vertices.size(); ++j) {
            if (vertices.at(j).label == startVertex) {
                startIndex = j;
            }
        }
        
        for (unsigned k = 0; k < vertices.size(); ++k) {
            if (vertices.at(k).label == endVertex) {
                endIndex = k;
            }
        }
        
        pair<int, int> p = make_pair(endIndex , edgeWeight);
        vertices.at(startIndex).neighbors.push_back(p);
    }
}

Graph::~Graph() {
    
}

void Graph::bfs() {
    Vertex * start;
    start = &vertices.at(0);
    string color = "WHITE";
    queue<Vertex *> q;
    vertices.at(0).distance = 0;
    q.push(start);
    Vertex * curr;
    
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        list<pair<int, int> >::iterator itr;
        
        for (itr = curr->neighbors.begin(); itr != curr->neighbors.end(); ++itr) {
            
            if (vertices.at(itr->first).color == "WHITE") {
                vertices.at(itr->first).color = "GRAY";
                vertices.at(itr->first).distance = curr->distance + itr->second;
                vertices.at(itr->first).prev = curr;
                q.push(&vertices.at(itr->first));
            }
        }
        
        curr->color = "BLACK";
            
    }
}

void Graph::dfs() {
    
    dfs_visit(vertices.at(0));
    
}

void Graph::dfs_visit(Vertex & curr) {
    if (curr.color == "WHITE") {
        curr.color = "BLACK";
        cout << curr.label << ",";
        
        list<pair<int, int> >::iterator itr;        
        for (itr = curr.neighbors.begin(); itr != curr.neighbors.end(); ++itr) {
            dfs_visit(vertices.at(itr->first));
        }
        
    }
    
}

void Graph::output_graph(const string & fileName) {
    ofstream outFS;
    
    outFS.open(fileName.c_str());
    
    outFS << "digraph G {" << endl;
    outFS << endl << endl;
    
    for (unsigned i = 0; i < vertices.size(); ++i) {
        
        if (vertices.at(i).distance != INT_MAX) {      
            outFS << vertices.at(i).label << " [color = lightblue, style = filled, label=\"" ;
            outFS << vertices.at(i).label << "," << vertices.at(i).distance << "\"];" << endl;
        }
    }
    
    outFS << endl << endl;
    
    for (unsigned j = 0; j < vertices.size(); ++j) {
        
        if (vertices.at(j).distance != INT_MAX) {
        
            list<pair<int, int> >::iterator itr;
            
            for (itr = vertices.at(j).neighbors.begin(); itr != vertices.at(j).neighbors.end(); ++itr) {
                
                outFS << vertices.at(j).label << " -> " << vertices.at(itr->first).label << ";" << endl;
                
            }
        }
    }
    
    outFS << endl << endl << "}";
    
    string jpgFilename = fileName.substr(0,fileName.size()-4)+".jpg";
    string command = "dot -Tjpg " + fileName + " -o " + jpgFilename;
    system(command.c_str());
    
    
}