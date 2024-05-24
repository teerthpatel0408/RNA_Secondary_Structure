/**
 * @file code_txt.cpp
 * @author Teerth Patel
 * @author Vasu Bhadja
 * @author Manthan Patel
 * @author Darsh Nayak
 * @brief  Solves RNA Folding problem by using Dynamic Programming over intervals.
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */



#include<iostream>
#include<ctime>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

map<pair<int,int>,int>mp;
vector<vector<int>>dp;
vector<pair<int,int>>vect;

/**
 * @brief Checks if the characters at the given positions in the string form a valid base pair in the RNA.
 * 
 * @param str RNA string that is to be processed.
 * @param a First index for the string
 * @param b Second index for the string
 * @return true 
 * @return false 
 */
bool isMatch(string&str,int a,int b){
    if((str[a]=='A' && str[b]=='U') || (str[b]=='A' && str[a]=='U'))    return true;
    if((str[a]=='C' && str[b]=='G') || (str[b]=='C' && str[a]=='G'))    return true;
    return false;
}


/**
 * @brief Calculates the minimum number of base pairs that can be formed in all intervals of a given RNA string
 * 
 * @param str RNA string
 * @param n Length of the RNA string
 */
void func(string&str, int n){
    for(int k=5;k<=n-1;k++){
        int i=0;
        int j=i+k;
        while(j<n){
            int val=dp[i][j-1];
            int finalT=-1;
            for(int t=i;t<j-4;t++){
                if(isMatch(str,j,t)){
                    if((((t-1<0)?0:dp[i][t-1])+dp[t+1][j-1]+1)>val){
                        val=((t-1<0)?0:dp[i][t-1])+dp[t+1][j-1]+1;
                        finalT=t;
                    }
                }
            }
            mp[{i,j}]=finalT;
            dp[i][j]=val;
            i++;
            j++;
        }
    }
}

/**
 * @brief Generates a pair out of 2 positions in the RNA String
 * 
 * @param i First position
 * @param j Second position
 */
void makePairs(int i,int j){
    if(i>=j-4){
        return;
    }
    int t=mp[{i,j}];
    if(t!=-1){
        vect.push_back({t,j});
        makePairs(i,t-1);
        makePairs(t+1,j-1);
    }
    else{
        makePairs(i,j-1);
    }
    return;
}

int main(){
    ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }
    high_resolution_clock::time_point time1, time2; // Declare the time points
    string input;
    getline(inputFile, input); // Read the input from the file
    int n=input.size();
    dp.resize(n,vector<int>(n,0));
    time1 = high_resolution_clock::now(); // Store the current time

    func(input,n);
    cout<<dp[0][n-1]<<endl;
    makePairs(0,n-1);
    inputFile.close(); // Close the input file
    time2 = high_resolution_clock::now(); // Store the current time
    auto duration = duration_cast<milliseconds>(time2 - time1);
    cout << "Time: " << duration.count() << " milliseconds" << endl;
    ofstream outputFile("output.txt"); // Open the output file
    if (!outputFile.is_open()) {
        cout << "Error opening output file." << endl;
        return 1;
    }

    outputFile << input << endl; // Write the input string to the output file
    for (auto i : vect) {
        outputFile << i.first << "," << i.second << endl; // Write pairs to the output file
    }
    outputFile.close(); // Close the output file
    return 0;
}