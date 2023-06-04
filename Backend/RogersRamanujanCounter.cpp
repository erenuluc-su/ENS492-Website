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
    for(unsigned long long i=1; i<k; i++){
        partitions += "K = " + to_string(i+1) + ",";
        for(unsigned long long x=0;x<n;x++){
            partitions += " n=" + to_string(x+1);
        }
        partitions += ",";
        for(unsigned long long x=0;x<m;x++){
            partitions += "m=" + to_string(x+1) + " ";
            for(unsigned long long y=0;y<n;y++)
            {
                partitions += table[i][x][y] + " ";  // display the current element out of the array
            }
            partitions += ",";  // when the inner loop is done, go to a new line
        }
        partitions += ",";
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
    RogersRamanujanCounter::show(table, ll_k, ll_m, ll_n);
    return table[k-1][m-1][n-1]; //returns the last element of the table
}

void RogersRamanujanCounter::print_vector(vector<int> list, bool format){ //prints results to txt
    if (format){
        for(int j=0;j<list.size();j++){
            partitions += to_string(list[j]);
            if(j+1 != list.size()){
                partitions += ";";
            }
        }
        partitions += ",";
    }
    else{
        for(int j=0;j<list.size();j++){
            partitions += to_string(list[j]);
            if(j+1 != list.size()){
                partitions += "+";
            }
        }
        partitions += ",";
    }
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

void RogersRamanujanCounter::rr1(int m, int n, bool format){ //rogers ramanujan for k = 2
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
    RogersRamanujanCounter::print_vector(nums, format);
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
            RogersRamanujanCounter::print_vector(nums, format);
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

void RogersRamanujanCounter::rr(int m, int n, int k, bool format){ //rogers ramanujan
    if(k < 2){
        partnum = "There are no partitions.";
        return;
    }
    if(k == 2){
        rr1(m, n, format);
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
    RogersRamanujanCounter::print_vector(nums, format);
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
            RogersRamanujanCounter::print_vector(nums, format);
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

void RogersRamanujanCounter::capconoperation(vector<vector<vector<int>>>& table, int a, int m, int n){ //edits one value on the table
    if((a>n && n!=0) || (m!=0 && n==0) || (m==0 && n!=0) || (n==1)){
        table[a-1][m][n] = 0; //zero case
        return;
    }
    if(m==1 || (m==0 && n==0)){
        table[a-1][m][n] = 1; //one case
        return;
    }
    int num1,num2,num3;
    if(a == 2){ //if a = 2
        if(m-2 < 0 || n-6*m+6 < 0){
            num2 = 0;
        }
        else{
            num2 = table[1][m-2][n-6*m+6];
        }
        if(m-1 < 0 || n-3*m+1 < 0){
            num3 = 0;
        }
        else{
            num3 = table[2][m-1][n-3*m+1];
        }
        table[a-1][m][n] = table[2][m][n] + num2 + num3;
        return;
    }
    if(a == 3){ //if a = 3
        if(m-1 < 0 || n-3*m < 0){
            num2 = 0;
        }
        else{
            num2 = table[2][m-1][n-3*m];
        }
        table[a-1][m][n] = table[3][m][n] + num2;
        return;
    }
    if(a == 4){ //if a = 4
        if(n-3*m < 0){
            num1 = 0;
        }
        else{
            num1 = table[1][m][n-3*m];
        }
        if(m-1 < 0 || n-6*m+2 < 0){
            num2 = 0;
        }
        else{
            num2 = table[1][m-1][n-6*m+2];
        }
        table[a-1][m][n] = num1 + num2;
        return;
    }
}

int RogersRamanujanCounter::cic(int m, int n){
    int a = 4;
    vector<vector<vector<int>>> table(a, vector<vector<int>>(m+1, vector<int>(n+1,9999))); //initialize table with all values at 0
    for(int k=0;k<=n;k++){
        for(int i=0;i<=m;i++){
            for(int j=a;j>=2;j--){
                RogersRamanujanCounter::capconoperation(table,j,i,k); //edit table
                if(j == 2 && i == m && k == n){
                    RogersRamanujanCounter::showcap(table, m, n);
                    return table[1][m][n]; //returns the correct element of the table
                }
            }
        }
    }
    return 0;
}

void RogersRamanujanCounter::print_partitions(vector<vector<int>> partition, bool format){
    if (format){
        for(int i=0;i<partition.size();i++){
            for(int j=0;j<partition[i].size();j++){
                partitions += to_string(partition[i][j]);
                if(j+1 != partition[i].size()){
                    partitions += ";";
                }
            }
            partitions += ",";
        }
    }
    else{
        for(int i=0;i<partition.size();i++){
            for(int j=0;j<partition[i].size();j++){
                partitions += to_string(partition[i][j]);
                if(j+1 != partition[i].size()){
                    partitions += "+";
                }
            }
            partitions += ",";
        }
    }
}

void RogersRamanujanCounter::capemoperation(vector<vector<vector<vector<vector<int>>>>>& table, int a, int m, int n){ //edits one value on the table
    //a, m and n corresponds to a-1, m and n on the table
    if((a>n && n!=0) || (m!=0 && n==0) || (m==0 && n!=0) || (n==1)){
        table[a-1][m][n]; //zero case
        return;
    }
    vector<int> temp;
    if(m==1 || (m==0 && n==0)){
        temp.push_back(n);
        table[a-1][m][n].push_back(temp); //one case
        return;
    }
    int num1,num2,num3;
    if(a == 2){ //if a = 2
        if(m-2 < 0 || n-6*m+6 < 0){
            num2 = 0;
        }
        else{
            for(int i=0;i<table[1][m-2][n-6*m+6].size();i++){ //add num2
                temp.clear();
                temp.push_back(2); //add 2
                temp.push_back(4); //add 4
                for(int j=0;j<table[1][m-2][n-6*m+6][i].size();j++){
                    if(table[1][m-2][n-6*m+6][i][j] != 0){
                        temp.push_back(table[1][m-2][n-6*m+6][i][j]+6); //increase all numbers by 6
                    }
                }
                table[a-1][m][n].push_back(temp);
            }
        }
        if(m-1 < 0 || n-3*m+1 < 0){
            num3 = 0;
        }
        else{
            for(int i=0;i<table[2][m-1][n-3*m+1].size();i++){ //add num3
                temp.clear();
                temp.push_back(2); //add 2
                for(int j=0;j<table[2][m-1][n-3*m+1][i].size();j++){
                    temp.push_back(table[2][m-1][n-3*m+1][i][j]+3); //increase all numbers by 3
                }
                table[a-1][m][n].push_back(temp);
            }
        }
        for(int i=0;i<table[2][m][n].size();i++){ //add num1
            table[a-1][m][n].push_back(table[2][m][n][i]);
        }
        return;
    }
    if(a == 3){ //if a = 3
        if(m-1 < 0 || n-3*m < 0){
            num2 = 0;
        }
        else{
            for(int i=0;i<table[2][m-1][n-3*m].size();i++){ //add num2
                temp.clear();
                temp.push_back(3); //add 3
                for(int j=0;j<table[2][m-1][n-3*m][i].size();j++){
                    temp.push_back(table[2][m-1][n-3*m][i][j]+3); //increase all numbers by 3
                }
                table[a-1][m][n].push_back(temp);
            }
        }
        for(int i=0;i<table[3][m][n].size();i++){ //add num1
            table[a-1][m][n].push_back(table[3][m][n][i]);
        }
        return;
    }
    if(a == 4){ //if a = 4
        if(n-3*m < 0){
            num1 = 0;
        }
        else{
            for(int i=0;i<table[1][m][n-3*m].size();i++){ //add num1
                temp.clear();
                for(int j=0;j<table[1][m][n-3*m][i].size();j++){
                    temp.push_back(table[1][m][n-3*m][i][j]+3); //increase all numbers by 3
                }
                table[a-1][m][n].push_back(temp);
            }
        }
        if(m-1 < 0 || n-6*m+2 < 0){
            num2 = 0;
        }
        else{
            for(int i=0;i<table[1][m-1][n-6*m+2].size();i++){ //add num2
                temp.clear();
                temp.push_back(4); //add 4
                for(int j=0;j<table[1][m-1][n-6*m+2][i].size();j++){
                    temp.push_back(table[1][m-1][n-6*m+2][i][j]+6); //increase all numbers by 6
                }
                table[a-1][m][n].push_back(temp);
            }
        }
        return;
    }
}

void RogersRamanujanCounter::cie(int m, int n, bool format){
    int a = 4;
    vector<vector<vector<vector<vector<int>>>>> table(a, vector<vector<vector<vector<int>>>>(m+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(0, vector<int>())))); //initialize table with all values being empty strings
    for(int k=0;k<=n;k++){
        for(int i=0;i<=m;i++){
            for(int j=a;j>=2;j--){
                //cout<<"a"<<endl;
                RogersRamanujanCounter::capemoperation(table,j,i,k); //edit table
                if(j == 2 && i == m && k == n){
                    RogersRamanujanCounter::print_partitions(table[1][m][n], format);
                    partnum = "There are a total of "+to_string(table[1][m][n].size())+" partitions.";
                }
            }
        }
    }
}

void RogersRamanujanCounter::showcap(vector<vector<vector<int>>>& table, unsigned long long m, unsigned long long n){
    for(unsigned long long i=1; i<4; i++){
        partitions += "A = " + to_string(i) + ",";
        for(unsigned long long x=0;x<n;x++){
            partitions += " n=" + to_string(x+1);
        }
        partitions += ",";
        for(unsigned long long x=0;x<m;x++){
            partitions += "m=" + to_string(x+1) + " ";
            for(unsigned long long y=0;y<n;y++)
            {
                partitions += to_string(table[i][x][y]) + " ";  // display the current element out of the array
            }
            partitions += ",";  // when the inner loop is done, go to a new line
        }
        partitions += ",";
    }
}

int RogersRamanujanCounter::min_next_num_noA(int num, int B, int C, int D){ //finds the next smallest possible number
    int result = 0;
    for(int i=1;i<=D;i++){
        if((2*num+i)%D == C){
            result = num + i;
        }
    }
    if(num + B < result){
        result = num + B + 1;
    }
    return result;
}

int RogersRamanujanCounter::min_next_num(int num, int B, int C, int D, int prev_num){ //finds the next smallest possible number

    if(num + B + 1 <= prev_num){
        return prev_num + 1;
    }

    int result = 0;
    for(int i=1;i<=(prev_num-num)+D;i++){
        if((2*num+i)%D == C && num + i > prev_num){
            result = num + i;
        }
    }
    if(num + B < result){
        result = num + B + 1;
    }
    
    return result;
}

int RogersRamanujanCounter::num_check_noA(int small_num, int big_num, int B, int C, int D){

    //return 0 = check failed
    //return 1 = check failed but next one might be succesful
    //return 2 = check succesful

    if(small_num >= big_num){
        return 0;
    }

    if(big_num - small_num > B){
        return 2;
    }

    if((small_num + big_num) % D == C){
        return 2;
    }

    return 1;

}

int RogersRamanujanCounter::num_check(int small_num, int prev_num, int big_num, int B, int C, int D){

    //return 0 = check failed
    //return 1 = check failed but next one might be succesful
    //return 2 = check succesful

    if(prev_num >= big_num){
        return 0;
    }

    if(big_num - small_num > B){
        return 2;
    }

    if((small_num + big_num) % D == C){
        return 2;
    }

    return 1;

}

void RogersRamanujanCounter::set_vector(vector<int> vect1, vector<int> & vect2){ //makes vect2 equal to vect1
    for(int i=0;i<vect1.size();i++){
        vect2[i] = vect1[i];
    }
}

int RogersRamanujanCounter::enumerator(int m, int n, int A, int B, int C, int D, int min_num, bool format){
    if(n == 1){
        partnum = "There is a total of 1 partition.";
        return 0;
    }

    if(m == 1){
        partnum = "There are no partitions.";
        return 1;
    }

    vector<int> nums(m, 0);
    for(int i=0;i<A;i++){ //fills the vector with initial values
        nums[i] = min_num+i;
    }
    for(int i=A;i<m-1;i++){ //fills the vector with initial values
        nums[i] = RogersRamanujanCounter::min_next_num(nums[i-A],B,C,D,nums[i-1]);
    }
    nums[m-1] = n - RogersRamanujanCounter::sum_vector(nums);

    if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2],nums[m-1],B,C,D) == 0){
        partnum = "There are no partitions.";
        return 0;
    }

    RogersRamanujanCounter::print_vector(nums, format);
    int total = 1;

    vector<int> temp_nums(m, 0);
    RogersRamanujanCounter::set_vector(nums,temp_nums);

    bool changed = false;
    bool p_flag = false;
    int phase = 0;
    while(true){
        if(phase == 0){
            if(m>2){
                if(m-A-2 >= 0){
                    if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 2 && RogersRamanujanCounter::num_check(nums[m-A-2],nums[m-3],nums[m-2]+1,B,C,D) == 2){
                        nums[m-1] = nums[m-1] - 1;
                        nums[m-2] = nums[m-2] + 1;
                        changed = true;
                    }
                    else if(RogersRamanujanCounter::num_check(nums[m-A-2],nums[m-3],nums[m-2]+1,B,C,D) == 1){
                        nums[m-1] = nums[m-1] - 1;
                        nums[m-2] = nums[m-2] + 1;
                    }
                    else if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 0 || RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 1){
                        p_flag = true;
                    }
                }
                else{
                    if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 2 && RogersRamanujanCounter::num_check_noA(nums[m-3],nums[m-2]+1,B,C,D) == 2){
                        nums[m-1] = nums[m-1] - 1;
                        nums[m-2] = nums[m-2] + 1;
                        changed = true;
                    }
                    else if(RogersRamanujanCounter::num_check_noA(nums[m-3],nums[m-2]+1,B,C,D) == 1){
                        nums[m-1] = nums[m-1] - 1;
                        nums[m-2] = nums[m-2] + 1;
                    }
                    else if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 0 || RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 1){
                        p_flag = true;
                    }
                }
            }
            else{
                if(RogersRamanujanCounter::num_check(nums[m-A-1],nums[m-2]+1,nums[m-1]-1,B,C,D) == 2){
                    nums[m-1] = nums[m-1] - 1;
                    nums[m-2] = nums[m-2] + 1;
                    changed = true;
                }
                else{
                    p_flag = true;
                }
            }
        }
        else{ //phase not zero
            if(phase != m-2){ // if not last phase
                RogersRamanujanCounter::set_vector(nums,temp_nums);
                if(temp_nums[m-3-phase]%D == D-C-1 && temp_nums[m-2-phase] - temp_nums[m-3-phase] == 2){ //increase num in correct position
                    temp_nums[m-2-phase] += 2;
                }
                else{ //increase num in correct position
                    temp_nums[m-2-phase] += 1;
                }
                for(int i=m-phase-1;i<m;i++){ //increase the rest of the nums according to their minimum values
                    if(i-A >= 0){
                        temp_nums[i] = RogersRamanujanCounter::min_next_num(temp_nums[i-A],B,C,D,temp_nums[i-1]);
                    }
                    else{
                        temp_nums[i] = RogersRamanujanCounter::min_next_num_noA(temp_nums[i-1],B,C,D);
                    }
                }
                temp_nums[m-1] = n - RogersRamanujanCounter::sum_vector(temp_nums) + temp_nums[m-1]; //set last num
    
                if(RogersRamanujanCounter::num_check(temp_nums[m-A-1],temp_nums[m-2],temp_nums[m-1],B,C,D) == 2){
                    changed = true;
                    RogersRamanujanCounter::set_vector(temp_nums,nums);
                    p_flag = false;
                }
                else{
                    RogersRamanujanCounter::set_vector(nums,temp_nums);
                    p_flag = true;
                }
            }
            else{ //if last phase
                RogersRamanujanCounter::set_vector(nums,temp_nums);
                temp_nums[m-2-phase] = temp_nums[m-2-phase] + 1; //increase num in correct position
                for(int i=m-phase-1;i<m;i++){ //increase the rest of the nums accordingly to their minimum values
                    temp_nums[i] = RogersRamanujanCounter::min_next_num_noA(temp_nums[i-1],B,C,D);
                }
                temp_nums[m-1] = n - RogersRamanujanCounter::sum_vector(temp_nums) + temp_nums[m-1]; //set last num
    
                if(RogersRamanujanCounter::num_check_noA(temp_nums[m-2],temp_nums[m-1],B,C,D) == 2){
                    changed = true;
                    RogersRamanujanCounter::set_vector(temp_nums,nums);
                    p_flag = false;
                }
                else{
                    RogersRamanujanCounter::set_vector(nums,temp_nums);
                    p_flag = true;
                }
            }
        }

        if(changed){
            RogersRamanujanCounter::print_vector(nums, format);
            total += 1;
            changed = false;
        }

        if(p_flag){ //nums[m-1] - nums[m-2-phase] < (phase + 2) * 2
            phase++;
            p_flag = false;
        }
        else{
            phase = 0;
        }

        if(phase + 1 == m){ //end condition
            partnum = "There are a total of "+to_string(total)+" partitions.";
            return total;
        }
    }
}