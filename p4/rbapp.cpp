
/* @author Kyle Kruskamp
 * @date April 28th 2016
 */
#include "rbtree.h"
#include "rbapp.h"
#include <iostream>

int main()
{
   RBapp appTree;
   appTree.mainLoop();
}

//set done to false
RBapp :: RBapp()
{
   done = false;
}

//flag for when to break loop
void RBapp :: mainLoop()
{
   while (!done)
   {
      processCommand();  
   }
}

//self explanatory
void RBapp :: processCommand()
{
   string word;
   string command;
   std :: cin >> command;

   if (command == "insert")
   {
      processInsert(word);
   }

   else if (command == "delete")
   {
      processDelete(word);
   }

   else if (command == "find")
   {
      processFind(word);
   }

   else if (command == "print")
   {
      processPrint();
   }

   else if (command == "quit")
   {
      done = true;
      processQuit();
   }
}

//call print tree on myRBT tree
void RBapp :: processPrint()
{
   myRBT.rbPrintTree();
}

/* 
 * Read in and find word
 save the infomration to data
 iterate through the vector and print dereferenced iterator.
 */
void RBapp :: processFind(string &)
{
   vector<const string*> data;
   vector<const string*> :: iterator iter;
   string word2;
   std :: cin >> word2;
   data = myRBT.rbFind(word2);

   for (iter = data.begin(); iter != data.end(); iter++)
   {
      std :: cout << word2 << " " << **iter << std :: endl;
   }
}

//reads in values and calls delete
void RBapp :: processDelete(string &data)
{
   string word;
   string value;
   value = data;
   std :: cin >> word;
   std :: cin >> value;
   myRBT.rbDelete(word, value);
}

//self explanatory
void RBapp :: processQuit()
{
   if (done)
   {
      return;
   }
}

//reads in strings and calls insert
void RBapp :: processInsert(string &word)
{
   string word2;
   std :: cin >> word >> word2;
   myRBT.rbInsert(word, word2);
}


