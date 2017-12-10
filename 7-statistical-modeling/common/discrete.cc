#ifndef COMMON_DISCRETE_H_
#define COMMON_DISCRETE_H_

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "base.cc"

using namespace std;

class DiscreteRandomGenerator : public RandomGenerator {
public:
  virtual double DistributionFunc(double) = 0;
  virtual double Probability(double) = 0;

  double DistributionInRange(double a, double b) {
    // For Discrete Distribution a is expected to be equal to b.
    // return DistributionFunc(a) - DistributionFunc(a-1);
    return Probability(a);
    // ATTENTION: this assumption might not be correct.
  }
};

class BernoulliDistribution : public DiscreteRandomGenerator {
public:
  BernoulliDistribution(double p) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter must be in [0,1] range.");
      return;
    }
    this->p = p;
    rg = new StandartRandomGenerator();
  }

  void BuildHistogram() {
    histogram.push_back(make_pair(0, 0));
    histogram.push_back(make_pair(1, 1));
  }

  double Next() { return (rg->Next() <= p ? 1 : 0); }

  double GetExpectation() { return p; }
  double GetDispersion() { return p * (1 - p); }
  double DistributionFunc(double k) {
    if (abs(k) < EPS) {
      return 1-p;
    } else if (abs(k-1) < EPS) {
      return 1;
    }
    return 0;
  }
  double Probability(double x) {
    if (abs(x) < EPS) {
      return 1-p;
    }
    return p;
  }

  ~BernoulliDistribution() { delete rg; }

private:
  double p;
  RandomGenerator* rg;
};

class BinomialDistribution : public DiscreteRandomGenerator {
public:
  BinomialDistribution(int m, double p) : m(m), p(p) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter p must be in [0,1] range.");
      return;
    }
  }

  void BuildHistogram() {
    for (int i = 0; i <= m; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  double Next() {
    int x = 0;
    StandartRandomGenerator rg;
    for (int i = 0; i < m; i++) {
      if (rg.Next() < p) {
        x++;
      }
    }
    return x;
  }

  double GetExpectation() { return m * p; }
  double GetDispersion() { return m * p * (1 - p); }
  double DistributionFunc(double x) {
    double val = 0;
    for (int i = 0; i <= x; i++) {
      val += c_coeff(m,i) * pow(p,i) * pow(1-p,m-i);
    }
    cout << "DISTR " << x << " -> " << val << endl;
    return val;
  }
  double Probability(double x) {
    return c_coeff(m, x) * pow(p, x) * pow(1-p, m-x);
  }

private:
  int m;
  double p;

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
  GeometricDistribution(double p) {
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
  double DistributionFunc(double x) { return 1 - pow(1-p, x); }
  double Probability(double x) { return p * pow(1-p, x-1); }

  void BuildHistogram() {
    histogram.clear();
    for (int i = 0; i < 20; i++) {
      histogram.push_back(make_pair(i, i));
    }
  }

  ~GeometricDistribution() { delete brg; }

private:
  double p;
  BaseRandomGenerator* brg;
};

#endif  // COMMON_DISCRETE_H_
