/*************************************************************
 *   Author:         Jody Hansen
 *   Date created:   04-20-2015
 *   File:           project1_3
 *
 **************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <sstream>


using namespace std;

int maxCrossSubarray(vector<int> &v, int lo, int hi){
    int sum = 0;
    int leftsum = INT_MIN;
    int rightsum = INT_MIN;
    int i, j;
    int mid = (lo+hi)/2;
    for(i = mid; i >= 0; i--){
        sum += v[i];
        if(sum > leftsum){
            leftsum = sum;
        }
    }
    
    sum = 0;
    
    for(j = mid+1; j <= hi; j++){
        sum += v[j];
        if(sum > rightsum){
            rightsum = sum;
        }
    }
   
    if(rightsum+leftsum <0){
        return 0;
    }
    return (leftsum + rightsum);
    
}

int maxSubarray(vector<int> &v, int lo, int hi){
    if (hi == lo) {
        return v[lo];
    }
    
    else{
        
        int mid = (lo + hi)/ 2;
        
        int left = maxSubarray(v, lo, mid);
        int right = maxSubarray(v, mid+1, hi);
        int cross = maxCrossSubarray(v, lo, hi);
        
        if(left >= right && left >= cross){
            return left;
        }
        
        else if(right >= left && right >= cross){
            return right;
        }
        
        else{
            return cross;
        }
    }
    
}



int main(int argc, char **argv) {
    
    ifstream ifile(argv[1]);
    string line;
    
    while (getline(ifile, line)) {
        std::vector<int> arr;
        std::stringstream ss(line);
        
        int i;
        
        cout<<line<<endl;
        
        while (ss >> i)
        {
            arr.push_back(i);
            
            if (ss.peek() == ',')
                ss.ignore();
        }
        
        int size = arr.size();
        
        
        int max_sum = maxSubarray(arr, 0, size-1);
        cout<<max_sum<<endl;
    }
    
    ifile.close();
    

    return 0;
};
