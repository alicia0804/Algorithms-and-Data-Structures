#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input;
    input.open("input2.txt");
    string line;
    int numberofline = 0;

    //we count the number of lines 
    while (getline(input, line)) {
        numberofline++;
    }
    input.close();

    input.open("input2.txt");

    //we create a 2d array to store the triangle
    vector<vector<int>> arr(numberofline);
    for (int i = 0; i < numberofline; i++) {
        for (int j = 0; j <= i; j++) {
            int val;
            input >> val;
            arr[i].push_back(val);
        }
    }
    input.close();

    int n = numberofline;

    //we create another array to store the max path sums
    vector<vector<int>> sum = arr;

    //we create an array to track the path taken
    vector<vector<int>> path(n, vector<int>(n, 0));

    //we start from the second last row to the top
    for (int i = n - 2; i >= 0; i--) { 
        for (int j = 0; j <= i; j++) {
            //for each position we add the maximum of the two elements 
            if (sum[i + 1][j] > sum[i + 1][j + 1]) {
                sum[i][j] += sum[i + 1][j];
                path[i][j] = j; 
            } else {
                sum[i][j] += sum[i + 1][j + 1];
                path[i][j] = j + 1; 
            }
        }
    }

    cout << sum[0][0] << endl;

    int temp = 0;
    for (int i = 0; i < n; i++) {
        cout << arr[i][temp] << " "; 
        temp = path[i][temp]; 
    }
    cout << endl;
}
