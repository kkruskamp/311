/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CensusData.h"
#include <time.h>
#include <math.h>
#include <random>

using std :: default_random_engine;

// formal parameter name commented out to avoid unused variable warning
void CensusData :: insertionSort(int type) 
{
   int i;
   Record *key;
   
   if (type == 0)
   {
      for (unsigned int j = 1; j < data.size(); j++)
      {
         key = data[j];
         i = j - 1;

         while (i >0 && data[i]->population > key->population)
         {
            data[i + 1] = data[i];
            i--;
         }
      }
   }

   if (type == 1)
   {
      for (unsigned int j = 1; j < data.size(); j++)
      {
         key = data[j];
         i = j - 1;

         while (i >0 && *(data[i]->city) > *(key->city))
         {
            data[i + 1] = data[i];
            i--;
         }
      }
   }
}


// formal parameter name commented out to avoid unused variable warning
void CensusData :: mergeSort(int type) 
{
   mergeSort(0, data.size() - 1 , type);
}

void CensusData :: mergeSort(int start, int end, int type)
{
   if (start < end)
   {
      int q = ( start + end ) / 2;
      mergeSort ( start, q, type );
      mergeSort ( ( q + 1 ), end, type );
      merge ( start, q, end, type );
   }
}

void CensusData :: merge(int start, int q, int end, int type)
{
   int firstIndex = q - start + 1;
   int secondIndex = end - q;
   vector < Record* > left;
   vector < Record* > right;

   for (int i = 0; i < firstIndex; i++)
   {
      left.push_back(data[start + i]);
   }

   for (int i = 0; i < secondIndex; i++)
   {
      right.push_back(data[q + i + 1]);
   }

   int l_size = left.size();
   int r_size = right.size();
   int l_iter = 0;
   int r_iter = 0;

   for (int i = start; i <= end; i++)
   {

      if ((l_iter < l_size) && (r_iter < r_size))
      {

         if (isSmaller(type, left[l_iter], right[r_iter]))
         {
            data[i] = left[l_iter];
            l_iter++;
         }

         else
         {
            data[i] = right[r_iter];
            r_iter++;
         }
      }

      else if (l_iter < l_size) 
      {
         data[i] = left[l_iter];
         l_iter++;
      }

      else
      {
         data [i] = right[r_iter];
         r_iter++;
      }
   }
}

bool CensusData :: isSmaller(int type, Record* c1, Record* c2)
{
   if (type == 0)
   {
      if (c1->population < c2->population)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      if (*c1->city < *c2->city)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
}

// formal parameter name commented out to avoid unused variable warning
void CensusData :: quickSort(int type) 
{
   randQuickSort(0, data.size() - 1, type);
}

void CensusData :: randQuickSort(int start, int end, int type)
{
   int q;
   if (start < end)
   {
      q = randPartition(start, end, type);
      randQuickSort(start, (q - 1), type);
      randQuickSort((q + 1), end, type);
   }
}

int CensusData :: randPartition(int start, int end, int type)
{
   std :: default_random_engine random_n(time(0));
   std :: uniform_int_distribution<int> i(start, end);
   Swap(data[i(random_n)], data[end]);
   return part(start, end, type);
}

int CensusData :: part(int start, int end, int type)
{

   Record *temp = data[end];
   int i = start - 1;

   for (int j = start; j <= end - 1; j++)
   {

      if (type == 0)
      {

         if (data[j]->population <= temp->population)
         {

            i++;
            Swap(data[i], data[j]);
         }
      }
      else
      {
         if (*data[j]->city <= *temp->city)
         {
            i++;
            Swap (data[i], data[j]);
         }
      }
   }
   Swap (data[i + 1], data[end]);
   return i + 1;
}

void CensusData :: Swap(Record *&c1, Record *&c2)
{
   Record *temp = c1;
   c1 = c2;
   c2 = temp;
}
