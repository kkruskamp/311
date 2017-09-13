/*@brief 
 * @author Kyle Kruskamp
 * Graph.cpp file
 * Date: May 18th 2016
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "minpriority.h"
#include "graph.h"
using std :: pair;
using std :: stringstream;
using std :: map;
using std :: endl;
using std :: vector;
using std :: swap;

Graph :: Graph() // constructor
{

}

Graph :: ~Graph() // destructor
{

}

//djekstras algorithm at work
void Graph :: BSSPtree(string source)
{
   for (map<string, Vertex> :: iterator iter = vert.begin(); iter != vert.end(); iter++)
   {
      iter->second.key = 100;
   }

   vert[source].pi = "nil";
   vert[source].key = 0;
   minQ.insert(vert[source].name, 0);
   string min = minQ.extractMin();

   while (min != "empty")
   {

      for (vector<Neighbor> :: iterator iter = adjList[min].begin(); iter != adjList[min].end(); iter++)
      {
         relax(vert[min].name, iter->name, iter->weight);
      }

      min = minQ.extractMin();
   }
}

// adjusts the rate of the path that u and v take
void Graph :: relax(string u, string v, int weight) 
{
   std :: cout << vert[v].key << endl;
   if (vert[v].key > (vert[u].key + weight))
   {
      vert[v].key = vert[u].key + weight;
      vert[v].pi = u;
      
      if (!(minQ.isMember(v)))
      {
         minQ.decreaseKey(v, vert[v].key);
      }
   }
}

//creates neighbors and pushes the neighbors onto the adjlist
//it then sorts them from beginning to end.
void Graph :: addEdge(string from, string to, int weight)
{
   Neighbor nNeighbor;
   nNeighbor.weight = weight;
   nNeighbor.name = to;
   adjList[from].push_back(nNeighbor);
   sort(adjList[from].begin(), adjList[from].end(), neighbor_Object);
}

void Graph :: addVertex(string vert_name)
{
   Vertex nVertex;
   nVertex.name = vert_name;
   nVertex.pi = "";
   nVertex.key = 100;

   //QUESTION ABOUT PAIR
   vert.insert(pair<string, Vertex>(vert_name, nVertex));
}

//get shortest path function finds the shortest path from a source to a node within the vector.
//it then sets the parent/pred and couts to output stream
//returns the string
string Graph :: getShortestPath(string from, string to)
{
   BSSPtree(from);
   string pred = "";
   stringstream stream;
   vector<string> nVector;

   pred = vert[to].name;
   nVector.push_back(pred);
   pred = vert[pred].pi;

   while (pred != vert[from].pi)
   {
      nVector.push_back(pred);
      pred = vert[pred].pi;
   }

   while (!nVector.empty())
   {
      stream << nVector.back() << "->";
      nVector.pop_back();
   }

   string sPath = stream.str();
   sPath.erase((sPath.length() - 2), 2);
   stream.str("");
   stream << sPath << " with length " << vert[to].key << endl;

   return stream.str();
}
