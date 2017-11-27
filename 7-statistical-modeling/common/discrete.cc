#ifndef COMMON_DISCRETE_H_
#define COMMON_DISCRETE_H_

#include <iostream>
#include <stdexcept>

#include "base.cc"

using namespace std;

class DiscreteRandomGenerator : public RandomGenerator {
public:
  DiscreteRandomGenerator(int dimension) : dimension(dimension) {}
  virtual double Distribution(double x) = 0;
  virtual vector<double>& Values() = 0;
  bool TestPearson(int sz = 1000) {
    vector<int> data(sz);
    for (int i = 0; i < sz; i++) {
      data[i] = this->Next();
    }
    vector<int> v(dimension);
    vector<double> x = Values();
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < dimension; j++) {
        if (x[j] == data[i]) {
          v[j]++;
          break;
        }
      }
    }
    double hi2 = 0;
    for (int i = 0; i < dimension; i++) {
      // TODO: to fix.
      double p = Distribution(x[i]);
      hi2 += ((v[i] - sz * p) * (v[i] - sz * p) * 1. / (sz * p));
    }
    cout << "Pearson test... ";
    if (hi2 < 16.92){
      cout << "passed with value" << hi2 << endl;
      return true;
    } else {
      cout << "failed with value " << hi2 << endl;
      return false;
    }
  }
  virtual ~DiscreteRandomGenerator() {}
protected:
  int dimension;
};

class BernoulliDistribution : public DiscreteRandomGenerator {
public:
  BernoulliDistribution(double p) : DiscreteRandomGenerator(2) {
    if (p < 0 || p > 1) {
      throw runtime_error("Parameter must be in [0,1] range.");
      return;
    }
    this->p = p;
    // mcg = new MultiplicativeCongruentialGenerator(4099, 4099, 2147483647);
    mcg = new StandartRandomGenerator();
    values = vector<double>{0.,1.};
  }
  double Distribution(double x) {
    if (x == 0.) {
      return 1 - p;
    } else if (x == 1.) {
      return p;
    } else {
      cout << "ALERT calling for " << x << endl;
      return -1.;
    }
  }
  vector<double>& Values() {
    return values;
  }
  double Next() {
    return (mcg->Next() <= p ? 1 : 0);
  }
  ~BernoulliDistribution() {
    delete mcg;
  }

private:
  double p;
  vector<double> values;
  RandomGenerator* mcg;
};

class BinomialDistribution : public RandomGenerator {
public:
  BinomialDistribution(int m, double p) : m(m), p(p), x(2) {}
  double Next() {
    StandartRandomGenerator rg(x);
    x++;
    vector<double> a(m);
    for (int i = 0; i < m; i++) {
      a[i] = rg.Next();
    }
    int x = 0;
    for (int i = 0; i < m; i++) {
    //  cout << a[i] << " ";
      x += (a[i] < p ? 1 : 0);
    }
  //  cout << endl;
    return x;
  }
private:
  int m;
  double p;
  int x;
};

#endif  // COMMON_DISCRETE_H_
