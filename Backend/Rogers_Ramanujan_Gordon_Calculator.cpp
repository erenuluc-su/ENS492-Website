#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "BigInt.hpp"

using namespace std;
ofstream output("output.txt"); //It writes the enumerations to this file

void print_vector(vector<int> list){ //prints results to txt
    for(int i=0;i<list.size();i++){
        output<<list[i];
        if(i != list.size()-1){
            output<<"+";
        }
    }
    output<<endl;
}

int sum_vector(vector<int> nums){ //sums all the integers in a vector
    int sum = 0;
    for(int i=0;i<nums.size();i++){
        sum += nums[i];
    }
    return sum;
}

bool phase_zero_k_check(vector<int> nums, int k){ //return true if no problem
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

int rr1(int m, int n){ //rogers ramanujan for k = 2
    if(m == 1){
        output<<n;
        output<<"There is a total of 1 partition."<<endl;
        output.close();
        return 1;
    }
    if(n < 1 || m < 1){
        output<<"There are no partitions."<<endl;
        output.close();
        return 0;
    }
    if(m*m > n){
        output<<"There are no partitions."<<endl;
        output.close();
        return 0;
    }
    vector<int> nums(m, 0);
    for(int i=0;i<m-1;i++){ //fils the vector with initial values (1,3,5,7...)
        nums[i] = 2*i+1;
    }
    nums[m-1] = n - sum_vector(nums); //first partition
    print_vector(nums);
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
                nums[m-1] = n - sum_vector(nums) + nums[m-1];
                changed = true;
            }
        }
        if(changed){
            print_vector(nums);
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
            output<<"There are a total of "<<total<<" partitions."<<endl;
            output.close();
            return total;
        }
    }
}

int rr(int m, int n, int k){ //rogers ramanujan
    if(k < 2){
        output<<"There are no partitions."<<endl;
        output.close();
        return 0;
    }
    if(k == 2){
        return rr1(m,n);
    }
    if((m*m) / (k-1) > n){
        output<<"There are no partitions."<<endl;
        output.close();
        return 0;
    }
    if(k > m+1){
        k = m+1;
    }
    vector<int> nums(m, 0);
    for(int i=0;i<m-1;i++){ //fils the vector with initial values (1,1,3,3...)
        nums[i] = 2*(i/(k-1))+1;
    }
    nums[m-1] = n - sum_vector(nums); //first partition
    print_vector(nums);
    vector<int> temp = nums;
    int total = 1;
    bool changed = false;
    bool check = false;
    int phase = 0;
    while(true){
        if(phase == 0){
            if(nums[m-1] - nums[m-2-phase] >= 2 && phase_zero_k_check(nums,k)){
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
                if(sum_vector(nums) > n){
                    nums = temp;
                    phase++;
                }
                else{
                    nums[m-1] = n - sum_vector(nums) + nums[m-1];
                    changed = true;
                    phase = 0;
                }
            }
            else{
                phase++; //phase increase
            }
        }
        if(changed){
            print_vector(nums);
            total += 1;
            changed = false;
        }
        if(phase + 1 == m){
            output<<"There are a total of "<<total<<" partitions."<<endl;
            output.close();
            return total;
        }
    }
}

void operation(vector<vector<vector<string>>>& table, unsigned long long a, unsigned long long m, unsigned long long n, unsigned long long k){ //edits one value on the table
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

void show (vector<vector<vector<string>>>& table, unsigned long long k, unsigned long long m, unsigned long long n){ //for debug
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

string rrgc(BigInt m, BigInt n, BigInt k){
    unsigned long long int ll_n = n.to_long_long();
    unsigned long long int ll_m = m.to_long_long();
    unsigned long long int ll_k = k.to_long_long();
    vector<vector<vector<string>>> table(ll_k, vector<vector<string>>(ll_m, vector<string>(ll_n,"0"))); //initialize table with all values at 0
    for(unsigned long long int j=1;j<=n;j++){
        for(unsigned long long int i=1;i<=m;i++){
            for(unsigned long long int a=1;a<=k;a++){
                operation(table,a,i,j,ll_k); //edit table
            }
        }
    }
    //show(table, ll_k, ll_m, ll_n); //Shows tables for debug!!!
    return table[ll_k-1][ll_m-1][ll_n-1]; //returns the last element of the table
}

int main(){
    BigInt program, m, n, k;
    cout <<"Rogers Ramanujan (Gordon) Calculator"<<endl;
    cout << "------------------------"<< endl;
    cout << "1. Partition Enumeration"<< endl;
    cout << "2. Partition Counter"<< endl;
    cout << "------------------------"<< endl;
    cout <<"Which program would you like to use? ";
    cin >> program;
    if(program == 2 || program == 1){
        cout<<"m: ";
        cin>>m;
        cout<<"n: ";
        cin>>n;
        cout<<"k: ";
        cin>>k;
    }
    if(program == 1){
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        cout<<"Done. Found "<<rr(m.to_int(), n.to_int(), k.to_int())<<" partitions."<<endl;
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        float time = float(chrono::duration_cast<chrono::milliseconds>(end - begin).count());
        cout<<"This took "<<time / 1000<<" seconds."<<endl;
    }
    else if(program == 2){
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        cout<<"There are "<<rrgc(m,n,k)<<" partitions."<<endl;
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        float time = float(chrono::duration_cast<chrono::milliseconds>(end - begin).count());
        cout<<"This took "<<time / 1000<<" seconds."<<endl;
    }
    else{
        cout<< "Program stops with input: "<< program << endl;
    }
    return 0;
}
