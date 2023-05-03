#ifndef H_ROGERSRAMANUJANCOUNTER_HPP
#define H_ROGERSRAMANUJANCOUNTER_HPP

using namespace std;

class RogersRamanujanCounter {
  public:
    RogersRamanujanCounter();
    string rrgc(int m, int n, int k);
    void rr(int m, int n, int k);
    string getPartitions();
    string getPartnum();
  
  private:
    void operation(vector<vector<vector<string>>>& table, unsigned long long a, unsigned long long m, unsigned long long n, unsigned long long k);
    void show (vector<vector<vector<string>>>& table, unsigned long long k, unsigned long long m, unsigned long long n);
    void rr1(int m, int n);
    void print_vector(vector<int> list);
    int sum_vector(vector<int> nums);
    bool phase_zero_k_check(vector<int> nums, int k);
    string partitions;
    string partnum;
};
#endif