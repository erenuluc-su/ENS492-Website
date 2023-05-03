#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "BigInt.hpp"
#include "RogersRamanujanCounter.hpp"

using namespace std;

// Define the constructor method of NewtonRaphson instances
RogersRamanujanCounter::RogersRamanujanCounter(){ 
    partitions = "";
    partnum = "";
}

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

void RogersRamanujanCounter::print_vector(vector<int> list){ //prints results to txt
    for(int i=0;i<list.size();i++){
        partitions += to_string(list[i]);
        if(i != list.size()-1){
            partitions += "+";
        }
    }
    partitions += ",";
}

int RogersRamanujanCounter::sum_vector(vector<int> nums){ //sums all the integers in a vector
    int sum = 0;
    for(int i=0;i<nums.size();i++){
        sum += nums[i];
    }
    return sum;
}

bool RogersRamanujanCounter::phase_zero_k_check(vector<int> nums, int k){ //return true if no problem
    if(nums.size()+1 == k){
        return true;
    }
    if(nums[nums.size()-1] - nums[nums.size()-2] != 2){
        return true;
    }
    for(int i=0;i<k-2;i++){
        if(nums[nums.size()-i-3] != nums[nums.size()-2]){
            return true;
        }
    }
    return false;
}

void RogersRamanujanCounter::rr1(int m, int n){ //rogers ramanujan for k = 2
    if(m == 1){
        partnum = "There is a total of 1 partition.";
        return;
    }
    if(n < 1 || m < 1){
        partnum = "There are no partitions.";
        return;
    }
    if(m*m > n){
        partnum = "There are no partitions.";
        return;
    }
    vector<int> nums(m, 0);
    for(int i=0;i<m-1;i++){ //fils the vector with initial values (1,3,5,7...)
        nums[i] = 2*i+1;
    }
    nums[m-1] = n - RogersRamanujanCounter::sum_vector(nums); //first partition
    RogersRamanujanCounter::print_vector(nums);
    int total = 1;
    bool changed = false;
    int phase = 0;
    while(true){
        if(phase == 0){
            if(nums[m-1] - nums[m-2-phase] >= (phase + 2) * 2){
                nums[m-1] = nums[m-1] - 1;
                nums[m-2] = nums[m-2] + 1;
                changed = true;
            }
        }
        else{
            if(nums[m-1] - nums[m-2-phase] >= (phase + 2) * 2){
                nums[m-2-phase] = nums[m-2-phase] + 1;
                for(int i=0;i<phase;i++){
                    nums[m-1-phase+i] = nums[m-2-phase+i] + 2;
                }
                nums[m-1] = n - RogersRamanujanCounter::sum_vector(nums) + nums[m-1];
                changed = true;
            }
        }
        if(changed){
            RogersRamanujanCounter::print_vector(nums);
            total += 1;
            changed = false;
        }
        if(nums[m-1] - nums[m-2-phase] < (phase + 2) * 2){
            phase++;
        }
        else{
            phase = 0;
        }
        if(phase + 1 == m){
            partnum = "There are a total of "+to_string(total)+" partitions.";
            return;
        }
    }
}

void RogersRamanujanCounter::rr(int m, int n, int k){ //rogers ramanujan
    if(k < 2){
        partnum = "There are no partitions.";
        return;
    }
    if(k == 2){
        rr1(m,n);
        return;
    }
    if((m*m) / (k-1) > n){
        partnum = "There are no partitions.";
        return;
    }
    if(k > m+1){
        k = m+1;
    }
    vector<int> nums(m, 0);
    for(int i=0;i<m-1;i++){ //fils the vector with initial values (1,1,3,3...)
        nums[i] = 2*(i/(k-1))+1;
    }
    nums[m-1] = n - RogersRamanujanCounter::sum_vector(nums); //first partition
    RogersRamanujanCounter::print_vector(nums);
    vector<int> temp = nums;
    int total = 1;
    bool changed = false;
    bool check = false;
    int phase = 0;
    while(true){
        if(phase == 0){
            if(nums[m-1] - nums[m-2-phase] >= 2 && RogersRamanujanCounter::phase_zero_k_check(nums,k)){
                nums[m-1] = nums[m-1] - 1;
                nums[m-2] = nums[m-2] + 1;
                changed = true;
            }
            else{
                phase++; //phase = 1
            }
        }
        if(phase > 0){
            if(nums[m-1] - nums[m-2-phase] >= phase - k + 5 || (k - phase == 3 && nums[m-1] - nums[m-2-phase] == 2)){
                temp = nums;
                nums[m-2-phase] = nums[m-2-phase] + 1; //initial increase
                for(int i=0;i<phase+1;i++){ //other increases on the right
                    if(m-1-phase+i <= k-2){ //check if conflict check is neccessary
                        nums[m-1-phase+i] = nums[m-2-phase+i];
                    }
                    else{
                        for(int j=0;j<k-2;j++){ //check if there is conflict on the left
                            if(!(nums[m-2-phase+i] == nums[m-3-phase+i-j] || nums[m-2-phase+i] - nums[m-3-phase+i-j] == 1)){
                                check = true; //no conflict if code enters here
                            }
                        }
                        if(check){ //no conflict
                            nums[m-1-phase+i] = nums[m-2-phase+i];
                            check = false;
                        }
                        else{ //yes conflict
                            if(nums[m-2-phase+i] == nums[m-k-phase+i]){ //if difference between last 2 numbers is 0, however this should be last k-1 numbers
                                nums[m-1-phase+i] = nums[m-2-phase+i] + 2;
                            }
                            else{ //if difference between last 2 numbers is 1
                                nums[m-1-phase+i] = nums[m-2-phase+i] + 1;
                            }
                        }
                    }
                }
                if(RogersRamanujanCounter::sum_vector(nums) > n){
                    nums = temp;
                    phase++;
                }
                else{
                    nums[m-1] = n - RogersRamanujanCounter::sum_vector(nums) + nums[m-1];
                    changed = true;
                    phase = 0;
                }
            }
            else{
                phase++; //phase increase
            }
        }
        if(changed){
            RogersRamanujanCounter::print_vector(nums);
            total += 1;
            changed = false;
        }
        if(phase + 1 == m){
            partnum = "There are a total of "+to_string(total)+" partitions.";
            return;
        }
    }
}

string RogersRamanujanCounter::getPartitions(){
    return partitions;
}

string RogersRamanujanCounter::getPartnum(){
    return partnum;
}