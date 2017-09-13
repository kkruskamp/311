/*@brief minpriority.cpp file
 * @author Kyle Kruskamp
 * Date: May 18th 2016
 */

#include <string>
#include <iostream>
#include "minpriority.h"

Minpriority :: Minpriority() //constructor
{
   heap_size = 0;
}

Minpriority :: ~Minpriority() //destructor
{

}

//returns parent of i
int Minpriority :: parent(int i)
{
   return ((i + 1) / 2) - 1;
}

//returns left child of i
int Minpriority :: left(int i)
{
   return (2 * (i + 1)) - 1;
}

//returns right child of i
int Minpriority :: right(int i)
{
   return (2 * (i + 1));
}

//creates min-heap
void Minpriority :: buildMinHeap()
{
   for (int i = (minHeap.size() / 2); i >= 0; i--)
   {
      minHeapify(i);
   }
}

//insert element push back onto vector and call decrease key on pushed in values
void Minpriority :: insert(string nID, int nKey)
{
   Element *ele = new Element;
   ele->key = nKey;
   ele->id = nID;
   heap_size++;
   minHeap.push_back(ele);
   decreaseKey(nID, nKey);
}

//changes key of ID if it matches one withint the minHeap
void Minpriority :: decreaseKey(string nID, int nKey)
{
   int pos = 0;
   Element *ele = nullptr;

   if (!minHeap.empty())
   {
      for (unsigned int i = 0; i <= minHeap.size() - 1; i++)
      {
         if (minHeap[i]->id == nID)
         {
            pos = i;
            
            if (nKey < minHeap[i]->key)
            {
               ele = minHeap[i];
               minHeap[pos]->key = nKey;
               
               while (pos > 0 && minHeap[parent(pos)]->key > minHeap[pos]->key)
               {
                  std :: swap(minHeap[parent(pos)], minHeap[pos]);
                  pos = parent(pos);
               }
            }

            else
            {
               return;
            }
         }
      }
   }
   
   //is element isnt empty set the key new and build the heap
   if (ele != nullptr)
   {
      ele->key = nKey;
      buildMinHeap();
   }
}


//pops off the min deletes element pointer and returns the ID of the min
string Minpriority :: extractMin()
{

   if(heap_size == 0)
   {
      return "empty";
   }

   Element *ele = minHeap[0];
   string eID = minHeap[0]->id;
   minHeap[0] = minHeap[heap_size - 1];
   minHeap.pop_back();
   buildMinHeap();
   heap_size--;
   delete ele;
   return eID;
}

//check to see if id from vector equals nID and if so returns t/f
bool Minpriority :: isMember(string nID)
{
   for (std :: vector<Element*> :: iterator iter = minHeap.begin(); iter != minHeap.end(); iter++)
   {
      if (nID == (*iter)->id)
      {
         return true;
      }
   }

   return false;
}

//keeps the min-heap propertys up to date
void Minpriority :: minHeapify(int i)
{  
   int l = left(i);
   int r = right(i);
   int min;

   if (l <= hSize && minHeap[l]->key < minHeap[i]->key)
   {
      min = l;
   }

   else
   {
      min = i;
   }

   if (r <= hSize && minHeap[r]->key < minHeap[min]->key)
   {
      min = r;
   }

   if(min != i)
   {
      std :: swap(minHeap[i], minHeap[min]);
      minHeapify(min);
   }
}
