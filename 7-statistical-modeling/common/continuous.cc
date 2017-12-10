#ifndef COMMON_CONTINUOUS_CC_
#define COMMON_CONTINUOUS_CC_

#include <cmath>

#include "base.cc"

class UniformDistribution : public ContinuousRandomGenerator {
public:
  UniformDistribution(double a, double b) : a(a), b(b) {
    brg = new StandartRandomGenerator();
  }

  double Next() { return (b - a) * brg->Next() + a; }

  double GetExpectation() { return (a + b) / 2; }
  double GetDispersion() { return (b - a) * (b - a) / 12; }
  double DistributionFunc(double x) {
    if (x < a) {
      return 0;
    } else if (x > b) {
      return 1;
    }
    return (x - a) / (b - a);
  }

  void BuildHistogram() {
    double step = (b - a) / 10.;
    for (double i = a; i <= b; i+=step) {
      histogram.push_back(make_pair(i, i+step));
    }
  }

  ~UniformDistribution() { delete brg; }

private:
  double a, b;
  BaseRandomGenerator* brg;
};

class StandartNormalDistribution : public ContinuousRandomGenerator {
public:
  StandartNormalDistribution() {
    brg = new StandartRandomGenerator();
  }

  double Next() {
    double sum = 0;
    for (int i = 0; i < 12; i++) {
      sum += brg->Next();
    }
    return sum - 6;
  }

  double GetExpectation() { return 0; }
  double GetDispersion() { return 1; }
  double DistributionFunc(double x) {
    double sum = 0;
    double step = 0.01;
    for (double t = -5; t < x; t += step) {
      sum += exp(-t*t/2) * step;
    }
    return sum / sqrt(M_PI * 2);
  }

  void BuildHistogram() {
    histogram.clear();
    for (int i = -5; i < 5; i++) {
      histogram.push_back(make_pair(i, i+1));
    }
  }

  ~StandartNormalDistribution() { delete brg; }

private:
  double mu, sigma2;
  BaseRandomGenerator* brg;
};

class ExponentialDistribution : public ContinuousRandomGenerator {
public:
  ExponentialDistribution(double lambda) {
    if (lambda <= 0) {
      throw runtime_error("Parameter must be greater than 0.");
      return;
    }
    this->lambda = lambda;
    brg = new StandartRandomGenerator();
  }

  double Next() { return - log(brg->Next()) / lambda; }
  double GetExpectation() { return 1 / lambda; }
  double GetDispersion() { return 1 / (lambda * lambda); }
  double DistributionFunc(double x) {
    return 1 - exp(-lambda * x);
  }

  void BuildHistogram() {
    histogram.clear();
    for (int i = 0; i < 10; i++) {
      histogram.push_back(make_pair(i, i+1));
    }
  }

  ~ExponentialDistribution() { delete brg; }

private:
  double lambda;
  BaseRandomGenerator* brg;
};

class LaplaceDistribution : public ContinuousRandomGenerator {
public:
  LaplaceDistribution(double lambda) {
    if (lambda <= 0) {
      throw runtime_error("Parameter must be greater than 0.");
      return;
    }
    this->lambda = lambda;
    brg = new StandartRandomGenerator();
  }

  double Next() {
    double y = brg->Next();
    return (y < 0.5 ? log(2 * y) / lambda : -log(2 - 2 * y) / lambda);
  }

  double GetExpectation() { return 0; }
  double GetDispersion() { return 2 / (lambda * lambda); }
  double DistributionFunc(double x) {
    return (x < 0 ? exp(lambda * x) / 2 : 1 - exp(-lambda * x) / 2);
  }

  void BuildHistogram() {
    histogram.clear();
    for (int i = -20; i < 20; i++) {
      histogram.push_back(make_pair(i, i+1));
    }
  }

  ~LaplaceDistribution() { delete brg; }

private:
  double lambda;
  BaseRandomGenerator* brg;
};

class LogisticDistribution : public ContinuousRandomGenerator {
public:
  LogisticDistribution(double mu, double k) : mu(mu) {
    if (k <= 0) {
      throw runtime_error("Parameter k must be greater than 0.");
      return;
    }
    this->k = k;
    brg = new StandartRandomGenerator();
  }

  double Next() {
    double y = brg->Next();
    return mu + k * log(y / (1 - y));
  }

  double GetExpectation() { return mu; }
  double GetDispersion() { return M_PI * M_PI * k * k / 3; }
  double DistributionFunc(double x) {
    return 1 / (1 + exp((mu - x) / k));
  }
  void BuildHistogram() {
    histogram.clear();
    for (int i = -5; i < 25; i++) {
      histogram.push_back(make_pair(i, i+1));
    }
  }

  ~LogisticDistribution() { delete brg; }

private:
  double mu, k;
  BaseRandomGenerator* brg;
};

#endif  // COMMON_CONTINUOUS_CC_
