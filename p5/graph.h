/*@brief graph.h
 * @author Kyle Kruskamp 
 * @date: May 18 2016
 */
#ifndef __GRAPH_H
#define __GRAPH_H

#include <string>
#include <vector>
#include <map>
#include "minpriority.h"
using std :: string;
using std :: map;
using std :: vector;

class Graph {

public:
    Graph();
    ~Graph();
    void addVertex(string vert_name);
    void addEdge(string from, string to, int weight);
    string getShortestPath(string from, string to);
      
private:
    class Vertex
    {
      public:
         string name;
         string pi; //predecessor identifier
         int key;
    };

    class Neighbor
    {
      public:
         string name;
         int weight;
    };
   
    struct nClass
    {
       bool operator() (Neighbor x, Neighbor y)
       {
          return (x.weight < y.weight);
       }
    } neighbor_Object;
    map<string, Vertex> vert;
    map<string, vector<Neighbor>> adjList;    
    Minpriority minQ;
    void BSSPtree(string source);
    void relax(string to, string from, int weight);

        
};

#endif
