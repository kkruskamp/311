/*@brief minpriority.h
 * @author Kyle Kruskamp
 * @date: may 18th 2016
 */

#ifndef __MINPRIORITY_H
#define __MINPRIORITY_H

#include <string>
#include <iostream>
#include <vector>
#include <string>
using std :: string;

class Minpriority {

public:
   Minpriority();
   ~Minpriority();
   void insert(string nID, int nKey);
   void decreaseKey(string nID, int nKey);
   string extractMin();
   bool isMember(string nID);

private:
   class Element
   {
     public:
       string id;
       int key;
   };
   
   std :: vector<Element*> minHeap;
   
   void buildMinHeap();
   void minHeapify(int i);
   int parent(int i);
   int left(int i);
   int right(int i);
   int heap_size;
};

#endif
