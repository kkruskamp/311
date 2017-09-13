#include <cstdlib>
#include <iostream>

using namespace std;

void insertion_sort(int arr[], int length);
void print_array(int array[],int size);

int main() {
   int length = 450000;
   int array[length];
   insertion_sort(array, length);
   return 0;
}

void insertion_sort(int arr[], int length) {

   int i, j ,tmp;
   for (i = 0; i < length; i++)
   {
      arr[i] = i;
   }

   for (i = 1; i < length; i++) {
      j = i;

      while (j > 0 && arr[j - 1] > arr[j]) {
         tmp = arr[j];
         arr[j] = arr[j - 1];
         arr[j - 1] = tmp;
         j--;
      }
 
  }
}

