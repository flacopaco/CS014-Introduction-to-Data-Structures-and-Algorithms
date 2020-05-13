#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; 
    const int NUMBERS_SIZE = 100000;

void Quicksort_midpoint(int numbers[], int i, int k);

void Quicksort_medianOfThree(int numbers[], int i, int k);

void InsertionSort(int numbers[], int numbersSize);

int Partition_midpoint(int numbers[], int i, int k);

int Partition_medianOfThree(int numbers[], int i, int k);

int genRandInt(int low, int high) {
return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main() {
    
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    
    fillArrays(arr1, arr2, arr3);
    
    clock_t Start1 = clock();
    Quicksort_medianOfThree(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End1 = clock();
    int elapsedTime1 = (End1 - Start1)/CLOCKS_PER_MS;
    // int elapsedTime1 = 4;

    
    clock_t Start2 = clock();
    Quicksort_midpoint(arr2, 0, NUMBERS_SIZE - 1);
    clock_t End2 = clock();
    int elapsedTime2 = (End2 - Start2)/CLOCKS_PER_MS;
    

    
    clock_t Start3 = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    clock_t End3 = clock();
    int elapsedTime3 = (End3- Start3)/CLOCKS_PER_MS;
    cout << "Times of medianOfThree, midpoint, and insertion on size 100,000" << endl;
    cout << elapsedTime1 << ", " << elapsedTime2 << ", " << elapsedTime3 << endl;

    
    // for (int x = 0; x < NUMBERS_SIZE - 1; ++x) {
    //     cout << arr2[x] << ", ";
    // }
    cout << endl;

    
    return 0;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition_midpoint(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
   
   return;
    
    
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition_medianOfThree(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_medianOfThree(numbers, i, j);
   Quicksort_medianOfThree(numbers, j + 1, k);
   
   return;
    
    
}

int Partition_midpoint(int numbers[], int i, int k) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;

   midpoint = (i + k) / 2;
   pivot = numbers[midpoint];
   
   l = i;
   h = k;
   
   while (!done) {
      
         while (numbers[l] < pivot) {
         ++l;
      }
        while (pivot < numbers[h]) {
         --h;
      }
      
      if (l >= h) {
         done = true;
      }
      else {

         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

int Partition_medianOfThree(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    // int median = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;
   
    int left = numbers[i];
    int right = numbers[k];
    int midpoint = (i + k) / 2;
    int mid = numbers[midpoint];

   
    if ((mid >= left && mid <= right) || (mid >= right && mid <= left)) {
        pivot = mid;
    } else if ((left <= mid && left >= right) || (left <= right && left >= mid)) {
        pivot = left;
    } else if((right <= mid && right >= left) || (right <= left && right >= mid)) {
        pivot = right;
    }
    


   
   l = i;
   h = k;
   
   while (!done) {
      
         while (numbers[l] < pivot) {
         ++l;
      }
        while (pivot < numbers[h]) {
         --h;
      }
      
      if (l >= h) {
         done = true;
         break;
      }
      else {

         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}


void InsertionSort(int numbers[], int numbersSize) {
   int i = 0;
   int j = 0;
   int temp = 0;  
   
   for (i = 1; i < numbersSize; ++i) {
      j = i;
     
      while (j > 0 && numbers[j] < numbers[j - 1]) {

         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
      }
   }
   
   return;
}

