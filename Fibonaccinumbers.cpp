#include <iostream>  
#include <fstream>   
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

//here we have a recursive function to calculate Fibonacci 
//number using naive approach 
//for this we have exponential time complexity O(2^n)
int naive(int n)
{
    //we have the base case for n = 0 and n = 1
    if (n < 2)
    {
        return n; 
    }
    else
    {
        //here we have recursive calls for our sequence
        return naive(n - 1) + naive(n - 2);
    }
}

//for the bottom-up dynamic programming approach we use an 
// array to store the values
//we are computing the fibonacci numbers using the array and 
//return the n-th number
int bottomup(int n)
{
    vector<int> arr(n + 1); 
    arr[0] = 0; 
    arr[1] = 1;  
    for (int i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 2] + arr[i - 1]; 
    }
    return arr[n];
}

//we are using Binet's formula to calculate the fibonacci numbers
int closedup(int n)
{
    double gold = (1 + sqrt(5.0)) / 2.0; 
    return round(pow(gold, n) / sqrt(5.0)); 
}

//we are computing fibonacci  numbers 
// using matrix exponentiation 
void multiply(long long F[2][2], long long M[2][2])
{
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(long long F[2][2], int n)
{
    if (n == 0 || n == 1)
        return;

    long long M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}

long long matrix(int n)
{
    if (n == 0)
        return 0;

    long long F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);
    return F[0][0];
}

int main()
{
    clock_t begin, end;  
    double time_spent;   
    int input = 0;
    ofstream out;
    //we open file to store execution times of naive Fibonacci function
    out.open("Naive_Data.txt");
    do
    {
        begin = clock(); 
        naive(input);    
        end = clock(); 
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out << input << " " << time_spent << endl;  
        input = input + 10; 
    //limited naive approach to 40 to prevent excessive runtime
    } while (input <= 40); 
    out.close(); 

    ofstream out1;
    //we open file to store execution times of bottom-up approach
    out1.open("Bottom_Data.txt");
    input = 0;
    do
    {
        begin = clock();
        bottomup(input);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out1 << input << " " << time_spent << endl;
        input = input + 10;
    } while (input <= 1000); 
    out1.close();

    ofstream out2;
    //we open file to store execution times 
    //of closed-form formula approach
    out2.open("Closed_Data.txt"); 
    input = 0;
    do
    {
        begin = clock();
        closedup(input);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out2 << input << " " << time_spent << endl;
        input = input + 10;
    } while (input <= 1000); 
    out2.close();

    ofstream out3;
    //we open another file to store execution 
    //times of matrix exponentiation
    out3.open("Matrix_Data.txt"); 
    input = 0;
    do
    {
        begin = clock();
        matrix(input);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out3 << input << " " << time_spent << endl;
        input = input + 10;
    } while (input <= 1000); 
    out3.close();

    return 0;
}
