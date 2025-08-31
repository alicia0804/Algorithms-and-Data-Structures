#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> countSort(vector<string>& arr, int pos) {
    vector<string> output(arr.size()); 
    int count[128] = {0}; 

    //counting the occurences of the characters
    for (size_t i = 0; i < arr.size(); i++) {
        unsigned char key = 0; 
        if (static_cast<size_t>(pos) < arr[i].length()) { 
            key = static_cast<unsigned char>(arr[i][pos]); 
        }
        count[key]++; 
    }

    for (int i = 1; i < 128; i++) {
        count[i] += count[i - 1]; 
    }

    //we build the output array by placing elements in correct order
    for (size_t i = arr.size(); i > 0; i--) {  
        unsigned char key = 0;
        if (static_cast<size_t>(pos) < arr[i - 1].length()) {
            key = static_cast<unsigned char>(arr[i - 1][pos]);
        }
        //we place element in correct position
        output[count[key] - 1] = arr[i - 1];
        count[key]--; 
    }

    return output;
}

vector<string> radixSort(vector<string> arr, size_t maxLen) {
    //we process characters from most significant position
    //to least significant
    for (int pos = static_cast<int>(maxLen) - 1; pos >= 0; pos--) {
        arr = countSort(arr, pos);
    }
    return arr;
}

int main() {
    vector<string> arr = {"word", "category", "cat", "new", "news", 
        "world", "bear", "at", "work", "time"};
    cout << "The unsorted array is: ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    size_t maxlen = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i].length() > maxlen) {
            maxlen = arr[i].length();
        }
    }

    arr = radixSort(arr, maxlen);

    cout << "The sorted array is: ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0; 
}
