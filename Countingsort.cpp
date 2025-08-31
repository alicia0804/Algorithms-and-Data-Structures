#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> countSort(vector<int>& inputarr) {
    //getting the size of the input array
    int n = inputarr.size();

    //we find the maximum element
    int m = 0;  
    for (int i = 0; i < n; i++) {
        m = max(m, inputarr[i]); 
    }

    //initialize the count array to 0
    vector<int> countarr(m + 1, 0);

    //counting occurences of the elements
    for (int i = 0; i < n; i++) {
        countarr[inputarr[i]]++; 
    }

    //we calculate the prefix sums to determine 
    //the position of elements in sorted order
    for (int i = 1; i <= m; i++) {
        countarr[i] += countarr[i - 1];  
    }

   //we create an output array to store the elements
    vector<int> outputarr(n);

    //sorting the elements
    for (int i = n - 1; i >= 0; i--) {
        outputarr[countarr[inputarr[i]] - 1] = inputarr[i];
        countarr[inputarr[i]]--;  
    }

    return outputarr;  
}

int main() {
    
    vector<int> inputarr = {9, 1, 6, 7, 6, 2, 1};

    vector<int> outputarr = countSort(inputarr);

    cout << "the sorted array is : ";
    for (size_t i = 0; i < outputarr.size(); i++) {
        cout << outputarr[i] << " ";
    }
    cout << endl;

    return 0;  
}
