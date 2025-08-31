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

//here we have a function that pushes down a node and 
// maintains the heap property
int pushdown(int arr[], int size, int root)
{
    int index = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

  //we return root if the left child doesn t exist
    if (left >= size)
    {
        return root;
    }

    //if we don't find a right child we swap it with left
    if (right >= size)
    {
        int temp = arr[left];
        arr[left] = arr[root];
        arr[root] = temp;
        return left;
    }

    //and we choose the larger child to swap with root
    if (arr[left] > arr[right])
    {
        index = left;
    }
    else
    {
        index = right;
    }

    //swapping the root with the larger child
    int temp2 = arr[root];
    arr[root] = arr[index];
    arr[index] = temp2;

    return pushdown(arr, size, index);
}

//this function checks the heap property
void checkheap(int arr[], int size, int root)
{
    int parent = (root - 1) / 2;
    if (arr[parent] < arr[root])
    {
        int temp = arr[root];
        arr[root] = arr[parent];
        arr[parent] = temp;
        
        checkheap(arr, size, root);
    }
}

//this function performs Heap Sort
void heapsort(int arr[], int size)
{
   
    buildmaxheap(arr, size);
    for (int i = size - 1; i >= 1; i--)
    {
        //swapping the largest element with the last element
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        size = size - 1; 

        //we restore max heap property
        int pos = pushdown(arr, size, 0);
        checkheap(arr, size, pos);
    }
}

int main()
{
    ofstream out;
    out.open("DataVariant.txt"); 

    srand(time(NULL)); 
    
    for (int size = 0; size < 100000; size = size + 1000)
    {
        int* arr = new int[size]; 
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand() % size;
        }

        
        auto start = high_resolution_clock::now();
        heapsort(arr, size);
        auto stop = high_resolution_clock::now(); 

        
        auto duration = duration_cast<microseconds>(stop - start);
        out << size << " " << (double)duration.count() << endl; 

        delete[] arr; 
    }
    return 0;
}
