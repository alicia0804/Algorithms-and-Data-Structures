#include <iostream>
#include <vector>
#include <algorithm>  
using namespace std;

//for Bucket Sort we create buckets, 
//distribute the numbers, sort the buckets
//and merge them
void bucketSort(vector<float>& arr) {
    int n = arr.size();  
    vector<vector<float>> buckets(n);//we create n buckets

    for (int i = 0; i < n; i++) {
        int index = n * arr[i];  
        //we put the elements in their bucket
        buckets[index].push_back(arr[i]);
    }

   //we sort them
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    //we merge the buckets back in the original array
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (float num : buckets[i]) {
            arr[idx++] = num;
        }
    }
}

int main() {
    vector<float> arr = {0.9, 0.1, 0.6, 0.7, 0.6, 0.3, 0.1};

    cout << "The original array: ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;

    bucketSort(arr); 

    cout << "the sorted array is: ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }    
    cout << endl;

    return 0;
}
