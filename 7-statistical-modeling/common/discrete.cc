#ifndef COMMON_DISCRETE_CC_
#define COMMON_DISCRETE_CC_

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "base.cc"
#include "constants.cc"

using namespace std;

class DiscreteRandomGenerator : public RandomGenerator {
public:
  DiscreteRandomGenerator(double xi) : RandomGenerator(xi) {
    if (xi == 0) {
      // Map does not contain the value.
      xi = DEFAULT_PEARSON_THRESHOLD;
      cout << "WARNING: Person threshold not found." << endl;
    }
  }
  virtual double Probability(double) = 0;

  double DistributionInRange(double a, double b) {
    // For Discrete Distribution a is expected to be equal to b.
    return Probability(a);
  }

  void RunTests(int sz = DEFAULT_TEST_SIZE) {
    RandomGenerator::RunTests(sz);

    string name = "Pearson test";
    PrintIntro(name);
    PrintTestResult(name, TestPearson());
  }
};

class BernoulliDistribution : public DiscreteRandomGenerator {
public:
  BernoulliDistribution(double p) : DiscreteRandomGenerator(XI_VALUES[2]) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter must be in [0,1] range.");
      return;
    }
    this->p = p;
    brg = new StandartRandomGenerator();
  }

  void BuildHistogram() {
    histogram.push_back(make_pair(0, 0));
    histogram.push_back(make_pair(1, 1));
  }

  double Next() { return (brg->Next() <= p ? 1 : 0); }

  double GetExpectation() { return p; }
  double GetDispersion() { return p * (1 - p); }
  double Probability(double x) {
    if (abs(x) < EPS) {
      return 1-p;
    }
    return p;
  }

  ~BernoulliDistribution() { delete brg; }

private:
  double p;
  BaseRandomGenerator* brg;
};

class BinomialDistribution : public DiscreteRandomGenerator {
public:
  BinomialDistribution(int m, double p) : DiscreteRandomGenerator(XI_VALUES[m+1]), m(m) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter p must be in [0,1] range.");
      return;
    }
    this->p = p;
    brg = new StandartRandomGenerator();
  }

  void BuildHistogram() {
    for (int i = 0; i <= m; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  double Next() {
    int x = 0;
    for (int i = 0; i < m; i++) {
      if (brg->Next() < p) {
        x++;
      }
    }
    return x;
  }

  double GetExpectation() { return m * p; }
  double GetDispersion() { return m * p * (1 - p); }
  double Probability(double x) {
    return c_coeff(m, x) * pow(p, x) * pow(1-p, m-x);
  }

  ~BinomialDistribution() { delete brg; }

private:
  int m;
  double p;
  BaseRandomGenerator* brg;

  // Calculates c^n_k.
  int c_coeff(int n, int k) {
    if (k == 0) {
      return 1;
    }
    long long ans = 1;
    for (int i = k+1; i <= n; i++) {
      ans *= i;
    }
    for (int i = 2; i <= n-k; i++) {
      ans /= i;
    }
    return ans;
  }
};

class GeometricDistribution : public DiscreteRandomGenerator {
public:
  GeometricDistribution(double p) : DiscreteRandomGenerator(XI_VALUES[20]) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter p must be in [0,1] range.");
      return;
    }
    this->p = p;
    brg = new StandartRandomGenerator();
  }

  double Next() { return ceil(log(brg->Next()) / log(1-p)); }
  double GetExpectation() { return 1 / p; }
  double GetDispersion() { return (1 - p) / (p * p); }
  double Probability(double x) { return p * pow(1-p, x-1); }

  void BuildHistogram() {
    histogram.clear();
    for (int i = 1; i <= 20; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  ~GeometricDistribution() { delete brg; }

private:
  double p;
  BaseRandomGenerator* brg;
};

class UniformDiscreteDistribution : public DiscreteRandomGenerator {
public:
  UniformDiscreteDistribution(int a, int b) : DiscreteRandomGenerator(XI_VALUES[b-a+1]), a(a), b(b) {
    brg = new StandartRandomGenerator();
  }

  double Next() { return (int)( (b-a+1) * brg->Next() + a * 1. ); }
  double GetExpectation() { return (a + b) / 2.; }
  double GetDispersion() { return (b - a + 1) * (b - a + 1) / 12.; }
  double Probability(double x) { return 1. / (b-a+1); }

  void BuildHistogram() {
    histogram.clear();
    for (int i = a; i <= b; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  ~UniformDiscreteDistribution() { delete brg; }
private:
  BaseRandomGenerator* brg;
  int a, b;
};

class PoissonDistribution : public DiscreteRandomGenerator {
public:
  PoissonDistribution(double lambda) : DiscreteRandomGenerator(XI_VALUES[21]) {
    if (lambda <= 0) {
      throw runtime_error("Parameter lambda must be in (0,inf) range.");
      return;
    }
    this->lambda = lambda;
    brg = new StandartRandomGenerator();
  }

  double Next() {
    double k = 0, prod = brg->Next();
    while (prod > exp(-lambda)) {
      prod *= brg->Next();
      k++;
    }
    return k;
  }

  double GetExpectation() { return lambda; }
  double GetDispersion() { return lambda; }
  double Probability(double x) {
    double val = exp(-lambda) * pow(lambda, x);
    for (int k = 2; k <= x; k++) {
      val /= k;
    }
    return val;
  }

  void BuildHistogram() {
    histogram.clear();
    for (int i = 0; i <= 20; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  ~PoissonDistribution() { delete brg; }

private:
  BaseRandomGenerator* brg;
  double lambda;
};

#endif  // COMMON_DISCRETE_CC_
