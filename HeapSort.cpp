#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

//this function maintains the max-heap property
void maxheapify(int arr[], int size, int root)
{
    int left = 2 * root + 1;
    int right = 2 * root + 2; 
    int largest;

    //we compare the left child with the root
    if (left < size && arr[left] > arr[root])
    {
        largest = left;
    }
    else
    {
        largest = root;
    }

    //we compare the right child with the largest so far
    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    //we swap if the largest is not the root
    if (largest != root)
    {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;

        //we recursively heapify the affected subtree
        maxheapify(arr, size, largest);
    }
}

//this function builds a max heap from an unordered array
void buildmaxheap(int arr[], int size)
{
    //we start from the last node that is not a leaf
    //and heapify each node
    for (int i = size / 2; i >= 0; i--)
    {
        maxheapify(arr, size, i);
    }
}

//we have a function that performs Heap Sort
void heapsort(int arr[], int size)
{
    //we first build a max heap from the array
    buildmaxheap(arr, size);

    //and then we extract elements from the heap one by one
    for (int i = size - 1; i >= 1; i--)
    {
        //we swap the largest elem with the last element
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        //reducing the heap size
        size = size - 1;


        //we restore the max heap property
        maxheapify(arr, size, 0);
    }
}

int main()
{
    ofstream out;
    out.open("DataNormalHeap.txt");

    srand(time(NULL)); 

    //we test heap sort with increasing input sizes
    for (int size = 0; size < 100000; size += 1000)
    {
        int* arr = new int[size]; 

        for (int i = 0; i < size; i++)
        {
            arr[i] = rand() % size;
        }

        //here we start measuring sorting time
        auto start = high_resolution_clock::now();
        heapsort(arr, size);
        auto stop = high_resolution_clock::now(); 

       //we compute the duration in seconds
        auto duration = duration_cast<microseconds>(stop - start);
        out << size << " " << (double)duration.count() << endl; 

        delete[] arr;
    }
}
