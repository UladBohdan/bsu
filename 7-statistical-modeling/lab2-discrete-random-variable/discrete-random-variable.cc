#include <iostream>

#include "../common/discrete.cc"

using namespace std;

int main() {
  try {
    BernoulliDistribution bd(0.2);
    vector<double> t(10000);
    int zeros = 0;
    for (int i = 0; i < 10000; i++) {
      t[i] = bd.Next();
      if (t[i] == 0) {
        zeros++;
      }
    }
    cout << "Zeros: " << zeros << "    Ones: " << 10000 - zeros << endl;
    cout << "running new Pearson..." << endl;
    bd.TestPearson();
    cout << "done." << endl;
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }

  BinomialDistribution bnd(20, 0.5);
  vector<int> v(10);
  for (int i = 0; i < 10000; i++) {
    v[bnd.Next()]++;
  }
  cout << "BINOMIAL:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << v[i] << " ";
  }
  cout << endl;

  return 0;
}
