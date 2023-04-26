#ifndef H_ROGERSRAMANUJANCOUNTER_HPP
#define H_ROGERSRAMANUJANCOUNTER_HPP

using namespace std;

class RogersRamanujanCounter {
  public:
    RogersRamanujanCounter();
    string rrgc(int m, int n);
  
  private:
    void operation(vector<vector<vector<string>>>& table, unsigned long long a, unsigned long long m, unsigned long long n, unsigned long long k);
    void show (vector<vector<vector<string>>>& table, unsigned long long k, unsigned long long m, unsigned long long n);
};
#endif