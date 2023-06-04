#ifndef H_ROGERSRAMANUJANCOUNTER_HPP
#define H_ROGERSRAMANUJANCOUNTER_HPP

using namespace std;

class RogersRamanujanCounter {
  public:
    RogersRamanujanCounter();
    string rrgc(int m, int n, int k);
    void rr(int m, int n, int k, bool format);
    string getPartitions();
    string getPartnum();
    int cic(int m, int n);
    void cie(int m, int n, bool format);
    int enumerator(int m, int n, int A, int B, int C, int D, int min_num, bool format);
  
  private:
    void operation(vector<vector<vector<string>>>& table, unsigned long long a, unsigned long long m, unsigned long long n, unsigned long long k);
    void show (vector<vector<vector<string>>>& table, unsigned long long k, unsigned long long m, unsigned long long n);
    void rr1(int m, int n, bool format);
    void print_vector(vector<int> list, bool format);
    int sum_vector(vector<int> nums);
    bool phase_zero_k_check(vector<int> nums, int k);
    void capconoperation(vector<vector<vector<int>>>& table, int a, int m, int n);
    void print_partitions(vector<vector<int>> partitions, bool format);
    void capemoperation(vector<vector<vector<vector<vector<int>>>>>& table, int a, int m, int n);
    void showcap(vector<vector<vector<int>>>& table, unsigned long long m, unsigned long long n);
    int min_next_num_noA(int num, int B, int C, int D);
    int min_next_num(int num, int B, int C, int D, int prev_num);
    int num_check_noA(int small_num, int big_num, int B, int C, int D);
    int num_check(int small_num, int prev_num, int big_num, int B, int C, int D);
    void set_vector(vector<int> vect1, vector<int> & vect2);

    
    string partitions;
    string partnum;
};
#endif