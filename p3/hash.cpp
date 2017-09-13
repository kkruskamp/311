/*
 * AUTHOR: KYLE KRUSKAMP
 * HASH FUNCTION DEFINITIONS
 
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "hash.h"

Hash :: Hash()
{
   collisions = 0;
   longestList = 0;
   counter = 0;
   numbers = 0;
   loader = 0;
}

/*Didnt realize .erase is a prebuilt function which helped greatly
 * if the word is found erase it and change the bool to true
 * if true reset counters and recount before finding avg list
 */

void Hash :: remove(string key)
{
   bool wordFound = false;

   for (int i = 0; i < HASH_TABLE_SIZE; i++)
   {
      for(std :: list<string> :: iterator iter = hashTable[i].begin(); iter != hashTable[i].end(); ++iter)
      {
         if (key == *iter)
         {
            iter = hashTable[i].erase(iter);
            loader--;
            wordFound = true;
            break;
         }
      }
   }
      
   if (wordFound == true)
      {
         counter = 0;
         numbers = 0;

         for (int i = 0; i < HASH_TABLE_SIZE; i++)
         {
            if (hashTable[i].empty() == false)
            {
               numbers += hashTable[i].size();
               counter++;
            }
         }

         runningAvgListLength = (runningAvgListLength + (numbers / counter)) / 2;
      }   
}

/*
 * iterates through and dereferences the word
 */

void Hash :: print()
{

   for (int i = 0; i < HASH_TABLE_SIZE; i++)
   {
      std :: cout << i << ":\t";

      for(std :: list<string> :: iterator iter = hashTable[i].begin(); iter != hashTable[i].end(); ++iter)
      {
         std :: cout << *iter << ", ";
      }   
   
      std :: cout << "\n";
   }
}

/*
 * Reads in file and calls the hash function to convert it to an int
 * indexs int word conversion and pushes word into that spot
 */

void Hash :: processFile(string file_name)
{
   string str;
   std :: ifstream fin(file_name);

   while (getline(fin, str))
   {                  
      int intWords = hf(str);

      if (hashTable[intWords].empty() == false)
      {
         collisions++;
      }

      hashTable[intWords].push_back(str);
      loader++;

      if (hashTable[intWords].size() > longestList)
      {
         longestList = hashTable[intWords].size();
      }

      numbers = 0;
      counter = 0;

      for (int i = 0; i < HASH_TABLE_SIZE; i++)
      {
         if (hashTable[i].empty() == false)
         {
            numbers += hashTable[i].size();
            counter++;
         }
      }

      runningAvgListLength = (runningAvgListLength + (numbers / counter)) / 2;
   }
   
   fin.close();
}

//basic search function

bool Hash :: search(string key)
{
   for (int i = 0; i < HASH_TABLE_SIZE; i++)
   {
      for(std :: list<string> :: iterator iter = hashTable[i].begin(); iter != hashTable[i].end(); ++iter)
      {
         if (key == *iter)
         {
            return true;
         }
      }
   }

   return false;
}

void Hash :: output(string file_name)
{
   std :: ofstream fout;
   fout.open(file_name);

   for (int i = 0; i < HASH_TABLE_SIZE; i++)
   {
      fout << i << ":" << "\t";

      for (std :: list<string> :: iterator iter = hashTable[i].begin(); iter != hashTable[i].end(); ++iter)
      {
         fout << *iter << "," << std :: endl;
      }
   }

   fout.close();
}

void Hash :: printStats()
{
   double load = loader / HASH_TABLE_SIZE;
   std :: cout << "Total Collisions = " << collisions << std :: endl;
   std :: cout << "Longest List Ever = " << longestList << std :: endl;
   std :: cout << "Average List Length Over Time = " << runningAvgListLength << std :: endl;
   std :: cout << "Load Factor = " << load << std :: endl;
}
