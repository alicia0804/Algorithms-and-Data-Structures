#include <iostream>         
#include <vector>            
#include <sstream>          
#include <algorithm>         
using namespace std;        

int main() {
    string line;                            
    getline(cin, line);              

    stringstream parser(line);              
    vector<int> nums;                   
    int temp;                                

    //we extract numbers from the stream one by one
    while (parser >> temp) {
        //we add each number to the nums vector
        nums.push_back(temp);
    }

    size_t size = nums.size();            
    vector<int> lengths(size, 1);          
    vector<int> links(size, -1);             

    //we loop through each element and the previous ones, 
    //we update LIS length at current index
    //abd store the previous index in the path
    for (size_t curr = 0; curr < size; curr++) {         
        for (size_t prev = 0; prev < curr; prev++) {       
            if (nums[curr] > nums[prev] && lengths[prev] + 1 > lengths[curr]) {
                lengths[curr] = lengths[prev] + 1;        
                links[curr] = prev;                      
            }
        }
    }

    int maxlen = lengths[0];               
    size_t lastpos = 0;                   
    for (size_t i = 1; i < size; i++) {  
        //we check if current length is greater than max  
        if (lengths[i] > maxlen) { 
            maxlen = lengths[i];        
            lastpos = i;
        }
    }

    vector<int> result;     
     //we backtrack to build the LIS                           
    for (int i = static_cast<int>(lastpos); i != -1; i = links[i]) { 
        result.push_back(nums[i]);                    
    }

    //we reverse the result to get the correct order
    reverse(result.begin(), result.end());        

    for (size_t i = 0; i < result.size(); i++) {    
        cout << result[i];                         
        if (i != result.size() - 1) cout << " ";     
    }

    cout << endl;                      
    return 0;                           
}
