#include <iostream>
#include <cstdlib>  
#include <ctime>   
using namespace std;

void Bubblesort(int arr[], int size)
{
    //we declared the variable temp to use when we swap
    //as well as a flag to check if the swapping was done
    int temp;
    bool swap;
    //this loop sees the number of passes in the array and resets
    //the swap at the beginning of each swap
    for (int i = 0; i < size - 1; i++)   
    {
        swap = false;
        //we swap if necessary
        for (int j = 0; j < size - 1 - i; j++)      
        {                                      
            if (arr[j] > arr[j + 1])   
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap = true;
            }
        } 
        //if we are done or the alg is sorted we exit
        if (!swap)
        {
            break;
        }
    }
}

int main()
{
    int size = 1000;
    int arr[size];

    srand(time(0)); 

    for (int i = 0; i < size; i++) 
    {
        arr[i] = rand() % size;
    }

    Bubblesort(arr, size);

    for (int i = 0; i < size; i++)      
    {
        cout << arr[i] << endl;
    }

    return 0;
}
