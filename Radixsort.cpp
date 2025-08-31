#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>  

using namespace std;

//we get the digit at a specific place value
int Digit(int value, int position) {
    return (value / position) % 10;
}

void recursiveRadixSort(vector<int>& data, int start, int end, int position) {
    //we stop if we have an element or no more digits
    if (start >= end || position == 0) return;

    vector<vector<int>> bins(10);

    //we put the numbers in buckets based on digits
    for (int i = start; i <= end; i++) {
        int digit = Digit(data[i], position);
        bins[digit].push_back(data[i]);
    }

    //we put the numbers back in the array
    int idx = start;
    for (int i = 0; i < 10; i++) {
        for (size_t j = 0; j < bins[i].size(); j++) {  
            data[idx++] = bins[i][j];
        }
    }

    //we sort each bucket recursively
    idx = start;
    for (int i = 0; i < 10; i++) {
        if (!bins[i].empty()) {
            recursiveRadixSort(data, idx, idx + bins[i].size() - 1, position / 10);
            idx += bins[i].size();
        }
    }
}

//we find the max number and the highest digit place 
void radixSort(vector<int>& data) {
    int maxValue = *max_element(data.begin(), data.end());  
    int position = pow(10, floor(log10(maxValue))); 
    recursiveRadixSort(data, 0, data.size() - 1, position);
}

int main() {
    vector<int> data = {450, 230, 560, 839, 719, 356};

    cout << "the unsorted array is ";
    for (size_t i = 0; i < data.size(); i++) cout << data[i] << " ";
    cout << endl;

    radixSort(data);

    cout << "the sorted array is ";
    for (size_t i = 0; i < data.size(); i++) cout << data[i] << " ";
    cout << endl;

    return 0;
}
