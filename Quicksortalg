#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//initialize i to point to the pivot position and if the 
//current element is smaller or equal to pivot we swap elements
int lomutoPartition(vector<int>& arr, int p, int q) {
    int pivot = arr[p];
    int i = p;
    int temp1, temp2;
    for (int j = p + 1; j < q; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp1;
        }
    }
    //swapping the pivot to its correct position
    temp2 = arr[p];
    arr[p] = arr[i];
    arr[i] = temp2;
    return i;
}

//here we have the Hoare Partition method
int hoarePartition(vector<int>& arr, int p, int q) {
    int pivot = arr[p];
    int i = p - 1, j = q + 1, temp3;
    while (true) {
    //we move i to the right until finding an element >= pivot
        do {
            i++;
        } while (arr[i] < pivot);
     //we move j to the left until finding an element <= pivot
        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) return j;//if i and j cross, return partition index
        temp3 = arr[i];
        arr[i] = arr[j];
        arr[j] = temp3;
    }
}

int motPartition(vector<int>& arr, int p, int q) {
    //finding the middle index
    int mid = (p + q) / 2;
    //we ensure last element is greater than first element
    if (arr[mid] < arr[p]) swap(arr[mid], arr[p]);
    if (arr[q] < arr[p]) swap(arr[q], arr[p]);
    if (arr[mid] < arr[q]) swap(arr[mid], arr[q]);
    return hoarePartition(arr, p, q);
}

//the conquer method for quicksort
void quicksort(vector<int>& arr, int p, 
    int r, int (*part)(vector<int>&, int, int)) {
    if (p < r) {
        int q = part(arr, p, r);
        quicksort(arr, p, q, part);
        quicksort(arr, q + 1, r, part);
    }
}

//generating a random array
vector<int> randomarray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int main() {
    srand(time(0));
    clock_t begin, end;
    double timespentLomuto = 0, timespentHoare = 0, timespentMedian = 0;
    int test = 0;
    const int numbers = 100000; 
    const int arraysize = 1000; 

    ofstream out("Lomuto.txt"), out1("Hoare.txt"), out2("Mediandata.txt");

    test = 0;
    while (test < numbers) {
        vector<int> arr = randomarray(arraysize);
        begin = clock();
        quicksort(arr, 0, arraysize - 1, lomutoPartition);
        end = clock();
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        timespentLomuto += time;
        out << test << " " << time << endl;
        test++;
    }
    out.close();

    
    test = 0;
    while (test < numbers) {
        vector<int> arr = randomarray(arraysize);
        begin = clock();
        quicksort(arr, 0, arraysize - 1, hoarePartition);
        end = clock();
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        timespentHoare += time;
        out1 << test << " " << time << endl;
        test++;
    }
    out1.close();

    test = 0;
    while (test < numbers) {
        vector<int> arr = randomarray(arraysize);
        begin = clock();
        quicksort(arr, 0, arraysize - 1, motPartition);
        end = clock();
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        timespentMedian += time;
        out2 << test << " " << time << endl;
        test++;
    }
    out2.close();

    
    cout << "Lomuto's average time is " << timespentLomuto / numbers 
    << " seconds" << endl;
    cout << "Hoare's average time is " << timespentHoare / numbers 
    << " seconds" << endl;
    cout << "Median-of-Three's average time is " << timespentMedian / numbers 
    << " seconds" << endl;

    return 0;
}
