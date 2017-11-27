#ifndef COMMON_BASE_CPP_
#define COMMON_BASE_CPP_

#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "constants.cc"

using namespace std;

class RandomGenerator {
public:
  virtual double Next() = 0;
  virtual ~RandomGenerator() {}
protected:
  void GenerateValues(int sz) {
    x = vector<double>(sz);
    for (int i = 0; i < sz; i++) {
      x[i] = Next();
    }
  }
  vector<double> x;
};

class BaseRandomGenerator : public RandomGenerator {
public:
  bool TestMoments(int sz = DEFAULT_TEST_SIZE) {
    GenerateValues(sz);
    double m = 0;
    for (int i = 0; i < sz; i++) {
      m += x[i];
    }
    m /= sz;
    cout << "Expectation: " << m << endl;
    double s2 = 0;
    for (int i = 0; i < sz; i++) {
      s2 += (x[i] - m) * (x[i] - m);
    }
    s2 /= (sz - 1);
    cout << "S2: " << s2 << endl;

    bool expTest = abs(m - 0.5) < EPS;
    bool dispTest = abs(s2 - 1./12) < EPS;

    cout << "math expectation test... " <<
      (expTest ? "passed." : "failed.") << endl;
    cout << "dispersion test..." <<
      (dispTest ? "passed." : "failed.") << endl;

    return expTest && dispTest;
  }

  bool TestPearson(int sz = DEFAULT_TEST_SIZE) {
    // p_k = 0.1 for each k = [0, 9];
    GenerateValues(sz);
    vector<double> v(10);
    for (int i = 0; i < sz; i++) {
      int gr = int(x[i] * 10);
      if (gr == 10) {
        gr = 9;
      }
      v[gr] += 1.;
    }
    double hi2 = 0;
    for (int i = 0; i < 10; i++) {
      hi2 += ((v[i] - sz * 0.1) * (v[i] - sz * 0.1) * 1. / (sz * 0.1));
    }
    return hi2 < PEARSON_THRESHOLD;
  }

  bool TestKolmogorov(int sz = DEFAULT_TEST_SIZE) {
    GenerateValues(sz);
    double mx = 0;
    vector<double> v(x.begin(), x.end());
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
      mx = max(mx, (i * 1. / sz) - v[i]);
    }
    mx *= sqrt(sz);
    return mx < KOLMOGOROV_THRESHOLD;
  }

  void RunTests(int sz = DEFAULT_TEST_SIZE) {
    string name = "Moments test";
    PrintIntro(name);
    PrintTestResult(name, TestMoments(sz));

    name = "Pearson test";
    PrintIntro(name);
    PrintTestResult(name, TestPearson(sz));

    name = "Kolmogorov test";
    PrintIntro(name);
    PrintTestResult(name, TestKolmogorov(sz));
  }

private:
  void PrintIntro(string name) {
    cout << "===== Running " << name << " =====" << endl;
  }
  void PrintTestResult(string name, bool result) {
    cout << setw(TEST_NAME_OUTPUT_WIDTH) << left << name <<
      (result ? COLOUR_GREEN + "PASSED" : COLOUR_RED + "FAILED")
        << COLOUR_DEFAULT << endl;
  }
};

class StandartRandomGenerator : public BaseRandomGenerator {
public:
  StandartRandomGenerator(int x = 1) {
    srand(time(NULL) * x);
  }
  double Next() {
    return (rand() % M) / (M * 1.);
  }
};

class MultiplicativeCongruentialGenerator : public BaseRandomGenerator {
public:
  MultiplicativeCongruentialGenerator(int x0, int a, int M) :
    a(a), M(M), cur(x0) { }
  double Next() {
    cur = (a * cur) % M;
    return cur * 1. / M;
  }
private:
  long long a, M;
  long long cur;
};

class MacLarenMarsagliaGenerator : public BaseRandomGenerator {
public:
  MacLarenMarsagliaGenerator(int k) : k(k), pos(0), M(100000007) {
    x = vector<double>(k);
    y = vector<double>(k);
    v = vector<double>(k);

    MultiplicativeCongruentialGenerator mcg(4099, 4099, 2147483647);
    StandartRandomGenerator srg(M);

    for (int i = 0; i < k; i++) {
      x[i] = mcg.Next();
      v[i] = x[i];
    }

    for (int i = 0; i < k; i++) {
      y[i] = srg.Next() + i;
    }
  }
  double Next() {
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

#endif  // COMMON_BASE_CPP_
