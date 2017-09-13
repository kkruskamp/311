/* This assignment originated at UC Riverside.*/
//AUTHOR: KYLE KRUSKAMP
//HASH FUNCTION
//APR 1 2016

#include <string>
#include "hash.h"

using std::string;

// This is only a sample hash function (and a bad one at that). You will
// need to replace the contents of this hash function with your own 
// hash function

/*
 * A common hash function that multiplies by 33, which is a prime number
 * I attempted using 37, 131, etc but found 33 most effective
 * The if statement may be redundant because I can't think of when the number would be negative
 * Resources/credit on understanding different functions
 * https://www.daniweb.com/programming/software-development/threads/231987/string-hash-function
*/

int Hash :: hf (string key)
{
   int sum = 0;
   for(unsigned int i = 0; i < key.length();  i++)
   {
      sum = 33 * sum + ((int)key[i]);
      sum %= HASH_TABLE_SIZE;
   }

   if(sum < 0)
   {
      sum += HASH_TABLE_SIZE;
   }
      
   return sum;
}
