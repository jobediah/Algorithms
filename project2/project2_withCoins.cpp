//
//  project2.cpp
//  CS325 Project2, Group 3
//  Spring 2015


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>
#include <random>
//#include <chrono>


using namespace std;
//using namespace std::chrono;

void getInput (const char * fileName, vector< vector<int> > & data)
{
    fstream inputFile;
    inputFile.open(fileName);
    while (inputFile) {
        const int bufferSize = 256;
        char buffer [bufferSize];
        inputFile.getline(buffer, bufferSize, '\n');
        string stringBuffer(buffer);
        replace( stringBuffer.begin(), stringBuffer.end(), ',', ' ');
        replace( stringBuffer.begin(), stringBuffer.end(), '[', ' ');
        replace( stringBuffer.begin(), stringBuffer.end(), ']', ' ');
        stringstream inputLine (stringBuffer);
        vector< int > lineData;
        while (inputLine) {
            int number;
            inputLine >> number;
            if (inputLine)
                lineData.push_back(number);
        }
        if (inputFile)
            data.push_back(lineData);
    }
}

int bruteforceCoin (vector<int>& input, vector<int>& number)
{
    int A = number[0];
    int n = input.size();
    int minimum, k, i, j;
    
    if(A <= 0){
        return 0;
    }
    
    minimum = INT_MAX;
    
    for(i = 0; i < n; i++){
        if(input[i] <= A){
            number[0] = A - input[i];
            minimum = min(minimum, bruteforceCoin(input, number) + 1);
        }
    }
    
    return minimum;
    
}



int dynamicCoin(vector<int>& input, vector<int>& number)
{
    int A = number[0];
    int n = input.size();
    int min, k, i, j;
    int* c;
    c = new int[A+1];
    c[0] = 0;
    
    //int* s;
    //s = new int[A+1];
    //int coin;
    //s[0] = 0;
    
    for(i = 1; i <= A; i++){
        min = INT_MAX;
        for(j = 0; j < n; j++){
            k = input[j];
            if(k <= i){
                if((1+ c[i-k]) < min){
                    min = 1 + c[i-k];
                    //coin = j;
                }
            }
            c[i] = min;
            //s[i] = coin; array to keep track of coins
            
        }
    }
    
    //Displays the coins used in algorithm
    /*k = A;
    while(k) {
        cout << input[s[k]] << " ";
        k = k - input[s[k]];
    }*/

    
    int total = c[A];
    delete [] c;
    //delete [] s;
    
    return total;
}

int main (int argc, char ** argv)
{
    ofstream output;
    //output.open("coinResults.txt");
    vector < vector< int > > input;
    getInput (argv[1], input);
    
    vector<int> values;
    int result;
    
    output << "Results for Algorithm 1: Brute force\n";
    for (vector < vector< int > >::iterator line = input.begin(); line != input.end(); line++) {
        values = *line;
        line++;
        //result = bruteforceCoin(values, *line);
        cout<<result<<endl;
    }
   
    output << "\nResults for Algorithm 2: Dynamic programming\n";
    for (vector < vector< int > >::iterator line = input.begin(); line != input.end(); line++) {
        values = *line;
        line++;
        result = dynamicCoin(values, *line);
        cout<<result<<endl;
    }
    
    return 0;
}

