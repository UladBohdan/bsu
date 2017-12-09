#ifndef COMMON_DISCRETE_H_
#define COMMON_DISCRETE_H_

#include <iostream>
#include <stdexcept>

#include "base.cc"

using namespace std;

class BernoulliDistribution : public RandomGenerator {
public:
  BernoulliDistribution(double p) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter must be in [0,1] range.");
      return;
    }
    this->p = p;
    rg = new StandartRandomGenerator();

    histogram.push_back(make_pair(0., p));
    histogram.push_back(make_pair(p, 1.));
  }

  double Next() { return (rg->Next() <= p ? 1 : 0); }

  double GetExpectation() { return p; }
  double GetDispersion() { return p * (1 - p); }
  double DistributionFunc(double k) {
    if (abs(k) < EPS) {
      return 0.;
    } else if (abs(k-p) < EPS) {
      return 1-p;
    } else {
      return 1.;
    }
  }

  ~BernoulliDistribution() { delete rg; }

private:
  double p;
  RandomGenerator* rg;
};

class BinomialDistribution : public RandomGenerator {
public:
  BinomialDistribution(int m, double p) : m(m), p(p) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter p must be in [0,1] range.");
      return;
    }

    for (int i = 0; i < m; i++) {
      histogram.push_back(make_pair(i*1./m, (i+1)*1./m));
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
    return x * 1. / m;
  }

  double GetExpectation() { return p; }
  double GetDispersion() { return m * p * (1 - p); }
  double DistributionFunc(double k) {
    double val = 0;
    if (abs(k) < EPS) {
      return 0;
    }
    for (int i = 0; i < k * m; i++) {
      val += c_coeff(m,i) * pow(p,i) * pow(1-p,m-i);
    }
    // cout << "DISTR " << k << " -> " << val << endl;
    return val;
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
/*
class GeometricDistribution : public RandomGenerator {
public:
  GeometricDistribution(double p) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter p must be in [0,1] range.");
      return;
    }


  }


};*/

#endif  // COMMON_DISCRETE_H_
