#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>  
#include <ctime>    

using namespace std;
using namespace std::chrono;

//selection sort algorithm
void SelectionSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[min] > arr[j])
                min = j;
        }
        if (min != i) {
            int aux = arr[min];
            arr[min] = arr[i];
            arr[i] = aux;
        }
    }
}

//geenerating random numbers for our average case
int* random(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    return arr;
}

//implement using a sorted array
int* sorted(int size) {  
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i; 
    }
    return arr;
}

int main() 
{
    srand(time(0)); 
    int *arr;
    ofstream out;
    out.open("SortedArrays.txt");

    for(int size = 0; size < 1000; size += 5) {
        //case A - most swapped involved - the worst case 
        //it happens when the largest element is the first
        //therefore we have to sort the whole array and 
        //then move the last element to the beginning
        arr = random(size);//we seed the random number generator
        if (size > 0) arr[0] = size; 
        auto start  = high_resolution_clock::now();
        SelectionSort(arr,size);
        auto stop = high_resolution_clock::now();
        auto worst_case = duration_cast<microseconds>(stop - start);
        delete[] arr; 

        //case B - least swapped involved - best case
        //we would supply an already sorted list to our list
        //just applying the sorted alg
        arr = sorted(size); 
        auto start1 = high_resolution_clock::now();
        SelectionSort(arr,size);
        auto stop1  = high_resolution_clock::now();
        auto best_case = duration_cast<microseconds>(stop1 - start1);
        delete[] arr; 

        //average case
        //we take 10 entries for each of the input to find 
        // out the best average case
        //we sum them all up and take out their average
        double sum = 0; 
        for( int i = 0;  i < 5; i++) {
            arr = random(size);
            auto start2 = high_resolution_clock::now();
            SelectionSort(arr,size);
            auto stop2 = high_resolution_clock::now();
            auto total = (duration_cast<microseconds>(stop2-start2));
            sum = sum + total.count();
            delete[] arr; 
        }
        double average_case = 0.0;
        average_case = sum / 5;

        out << size << " " << (double) worst_case.count() << " " 
            << (double)best_case.count() << " " << average_case << endl;
    }
    out.close();
    return 0;
}
