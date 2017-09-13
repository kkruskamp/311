#include <iostream>
using namespace std;

int main()
{
   int sum = 0;

   for (int i = 1; i < 40000000; i++)
   {
     sum += i;
   }

   cout << sum << endl;

   return 0;
}
