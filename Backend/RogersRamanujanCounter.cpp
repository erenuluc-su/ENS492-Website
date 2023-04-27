#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "BigInt.hpp"
#include "RogersRamanujanCounter.hpp"

using namespace std;

// Define the constructor method of NewtonRaphson instances
RogersRamanujanCounter::RogersRamanujanCounter(){}

void RogersRamanujanCounter::operation(vector<vector<vector<string>>>& table, unsigned long long a, unsigned long long m, unsigned long long n, unsigned long long k){ //edits one value on the table
    //cout<<"calculating a "<<a<<" m "<<m<<" n "<<n<<endl; //for debug
    //a, m and n corresponds to a-1, m-1 and n-1 on the table
    if(m>n || (m==n && a<=m)){
        table[a-1][m-1][n-1] = "0"; //zero case
        return;
    }
    if(m==1 || (m==n && a>m)){
        table[a-1][m-1][n-1] = "1"; //one case
        return;
    }
    if(a==1){
        table[a-1][m-1][n-1] = table[k-a][m-a][n-m-1]; //first element is zero in this case
        return;
    }
    if(m-a+1 <= 0){
        table[a-1][m-1][n-1] = table[a-2][m-1][n-1]; //second element is zero in this case
        return;
    }
    table[a-1][m-1][n-1] = (BigInt(table[a-2][m-1][n-1]) + BigInt(table[k-a][m-a][n-m-1])).to_string();
    return;
}

void RogersRamanujanCounter::show (vector<vector<vector<string>>>& table, unsigned long long k, unsigned long long m, unsigned long long n){ //for debug
    for(unsigned long long i=0; i<k; i++){
        cout<<endl;
        cout<< "A = "<< i <<endl;
        for(unsigned long long x=0;x<m;x++){
            for(unsigned long long y=0;y<n;y++)  // loop for the three elements on the line
            {
                cout<< table[i][x][y] << " ";  // display the current element out of the array
            }
            cout<<endl;  // when the inner loop is done, go to a new line
        }
        cout<<endl;
    }
}

string RogersRamanujanCounter::rrgc(int m, int n, int k){
    unsigned long long int ll_k = (unsigned long long) k;
    unsigned long long int ll_n = (unsigned long long) n;
    unsigned long long int ll_m = (unsigned long long) m;
    vector<vector<vector<string>>> table(ll_k, vector<vector<string>>(ll_m, vector<string>(ll_n,"0"))); //initialize table with all values at 0
    for(unsigned long long int j=1;j<=ll_n;j++){
        for(unsigned long long int i=1;i<=ll_m;i++){
            for(unsigned long long int a=1;a<=ll_k;a++){
                RogersRamanujanCounter::operation(table,a,i,j,ll_k); //edit table
            }
        }
    }
    //show(table, ll_k, ll_m, ll_n); //Shows tables for debug!!!
    return table[k-1][m-1][n-1]; //returns the last element of the table
}