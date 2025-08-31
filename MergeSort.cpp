#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>   
#include <algorithm> 
#include <random> 

using namespace std;
using namespace std::chrono;

//we have this function that merges two sorted subarrays 
//into a single sorted array
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int leftarr = m - l + 1;
    int rightarr = r - m;

    //we use them to store our arrays
    int L[leftarr], R[rightarr];
    for (i = 0; i < leftarr; i++)
        L[i] = arr[l + i];
    for (j = 0; j < rightarr; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    //we merge the subarrays back to the main array
    while (i < leftarr && j < rightarr)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < leftarr)
    {
        arr[k++] = L[i++];
    }

    while (j < rightarr)
    {
        arr[k++] = R[j++];
    }
}

//we go through the subarray from the second to the last element
//and we compare each element with the previous element and shift them
//to the right if they are greater than the current element
//we insert the current element in the good position
void insertionSort(int arr[], int l, int r)
{
    int i, key, j;
    for (i = l + 1; i <= r; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= l && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
//this function breaks down the array using the divide and conquer method
//to break the problem into smaller parts 
void mergeSort(int arr[], int l, int r, int k)
{
    if ((r - l) <= k)
    {
        insertionSort(arr, l, r);
    }
    else
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m, k);
        mergeSort(arr, m + 1, r, k);
        merge(arr, l, m, r);
    }
}

int main()
{
    //we need a better measurement for the data this is why i increased
    //the size
    int size = 5000; 
    int arr[size];
    ofstream out;
    out.open("Data.txt");
    //we calculated the random seed initialization outside the loop
    srand(time(NULL));

    for (int k = 0; k < size; k = k + 50) 
    {
       //here we have the best case scenario which is the sorted array
        for (int i = 0; i < size; i++)
        {
            arr[i] = i;
        }

        auto start1 = high_resolution_clock::now();
        mergeSort(arr, 0, size - 1, k);
        auto stop1 = high_resolution_clock::now();
        //we will be using microseconds for the algorithm
        auto best_case = duration_cast<microseconds>(stop1 - start1);

        //average case scenario is just creating a random array
        for (int i = 0; i < size; i++)
        {
            arr[i] = i;
        }
        //we use a random engine for shuffling the numbers 
        std::default_random_engine engine(rand());
        shuffle(arr, arr + size, engine);

        auto start2 = high_resolution_clock::now();
        mergeSort(arr, 0, size - 1, k);
        auto stop2 = high_resolution_clock::now();
        auto average_case = duration_cast<microseconds>(stop2 - start2);

      //the worst case scenario for us is to have the 
      // numbers in a descending order
        for (int i = 0; i < size; i++)
        {
            arr[i] = size - i;
        }

        auto start3 = high_resolution_clock::now();
        mergeSort(arr, 0, size - 1, k);
        auto stop3 = high_resolution_clock::now();
        auto worst_case = duration_cast<microseconds>(stop3 - start3);

       //we print all the results in the file and we close the file
        out << k << " " << (double)worst_case.count() << " " 
        << (double)best_case.count() << " " << (double)average_case.count() << endl;
    }
    out.close();
    return 0;
}
