/*@brief sspapp.cpp
 * @author Kyle Kruskamp
 * Date: May 18th 2016
 */

#include <iostream>
#include <string>
#include "minpriority.h"
#include "graph.h"
#include "sspapp.h"
#include <cctype>

//main, creates SSPapp object and calls process on it.
int main()
{
  SSPapp app;
  app.process();
  return 0;
}

//process input file and creates verts, edges, and path
void SSPapp :: process()
{
   int value, weight;
   string vert, vert2;

   cin >> value;

   for (int i = 0; i < value; i++)
   {
      cin >> vert;
      nGraph.addVertex(vert);
   }

   cin >> value;

   for (int i = 0; i < value; i++)
   {
      cin >> vert;
      cin >> vert2;
      cin >> weight;
      nGraph.addEdge(vert, vert2, weight);
   }

   while (!(cin.eof()))
   {
      cin >> vert;
      cin >> vert2;
      nGraph.getShortestPath(vert, vert2);
   }
}
