#include <cmath>
#include <iostream>
#include <random>
#include <time.h>

// #include "../common/continuous.cc"

const int N = 8000;

using namespace std;

int main() {
  srand(time(NULL));
  //StandartNormalDistribution rg;

  cout << "-----------------" << endl
       << "One-dimensional integral on [-inf, inf]: e^(-x^2)*sqrt(1+x^2)" << endl;

  default_random_engine generator;
  normal_distribution<double> distribution(0,1./sqrt(2));

  double ans = 0;
  for (int i = 0; i < N; i++) {
    double x = distribution(generator);
    ans += sqrt(M_PI * (1 + x * x));
  }
  ans /= N;
  cout << "ANSWER: " << ans << endl
       << "-----------------" << endl;
  return 0;
}
