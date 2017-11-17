#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../common/test.h"

using namespace std;

const int SIZE = 5000;
const int INIT_VALUE = 4099;

class MultiplicativeCongruentialGenerator {
public:
  MultiplicativeCongruentialGenerator(int x0, int a, int M) :
    x0(x0), a(a), M(M), cur(x0) { }

  double Next() {
    cur = (a * cur) % M;
    return cur * 1. / M;
  }
private:
  long long a, M, x0;
  long long cur;
};

class MacLarenMarsagliaGenerator {
public:
  MacLarenMarsagliaGenerator(int k) : k(k), pos(0), M(100000007) {
    x = vector<double>(k);
    y = vector<double>(k);
    v = vector<double>(k);

    MultiplicativeCongruentialGenerator mcg(INIT_VALUE, INIT_VALUE, 2147483647);
    for (int i = 0; i < k; i++) {
      x[i] = mcg.Next();
      v[i] = x[i];
    }

    srand(M);

    for (int i = 0; i < k; i++) {
      y[i] = (rand() % M) / M;
    }
  }

  int Next() {
    int i = y[pos] * k;
    double r = v[i];
    v[i] = x[(pos + k) % k];
    return r;
  }
private:
  int k, M;
  vector<double> x, y, v;
  int pos;
};

int main() {
  cout << "===== Running Multiplicative Congruential Generator" << endl;
  MultiplicativeCongruentialGenerator mcg(INIT_VALUE, INIT_VALUE, 2147483647);
  vector<double> x(SIZE);
  for (int i = 0; i < SIZE; i++) {
    x[i] = mcg.Next();
  }
  MomentsTest(x);
  PearsonTest(x);
  KolmogorovTest(x);

  cout << "===== Running MacLaren-Marsaglia Generator" << endl;
  MacLarenMarsagliaGenerator mmg(20000);
  vector<double> y(SIZE);
  for (int i = 0; i < SIZE; i++) {
    y[i] = mcg.Next();
  }
  MomentsTest(y);
  PearsonTest(y);
  KolmogorovTest(y);
}
