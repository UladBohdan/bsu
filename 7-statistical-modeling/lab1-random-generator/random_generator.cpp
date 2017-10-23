#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

const double EPS = 0.01;
const double PEARSON_THRESHOLD = 16.92;
const double KOLMOGOROV_THRESHOLD = 1.36;
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

void MomentsTest(const vector<double>& x) {
  int n = x.size();

  double m = 0;
  for (int i = 0; i < n; i++) {
    m += x[i];
  }
  m /= n;
  cout << "Expectation: " << m << endl;
  double s2 = 0;
  for (int i = 0; i < n; i++) {
    s2 += (x[i] - m) * (x[i] - m);
  }
  s2 /= (n - 1);
  cout << "S2: " << s2 << endl;

  cout << "math expectation test... " <<
    (abs(m - 0.5) < EPS ? "passed." : "failed.") << endl;
  cout << "dispersion test..." <<
    (abs(s2 - 1./12) < EPS ? "passed." : "failed.") << endl;
}

void PearsonTest(const vector<double>& x) {
  // p_k = 0.1 for each k = [0, 9];
  int n = x.size();
  vector<double> v(10);
  for (int i = 0; i < n; i++) {
    int gr = int(x[i] * 10);
    if (gr == 10) {
      gr = 9;
    }
    v[gr] += 1.;
  }
  double hi2 = 0;
  for (int i = 0; i < 10; i++) {
    hi2 += ((v[i] - n * 0.1) * (v[i] - n * 0.1) * 1. / (n * 0.1));
  }
  cout << "Pearson test... ";
  if (hi2 < PEARSON_THRESHOLD){
    cout << "passed." << endl;
  } else {
    cout << "failed with value " << hi2 << endl;
  }
}

void KolmogorovTest(const vector<double>& x) {
  int n = x.size();
  double mx = 0;
  vector<double> v(x.begin(), x.end());
  sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++) {
    mx = max(mx, (i * 1. / n) - v[i]);
  }
  cout << "Kolmogorov test... ";
  mx *= sqrt(n);
  if (mx < KOLMOGOROV_THRESHOLD) {
    cout << "passed." << endl;
  } else {
    cout << "failed with value " << mx << endl;
  }
}

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
