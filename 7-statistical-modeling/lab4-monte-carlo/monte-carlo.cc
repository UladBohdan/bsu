#include <cmath>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

#include "../common/continuous.cc"
#include "../common/discrete.cc"

const int N = 8000;

using namespace std;

int main() {
  srand(time(NULL));

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
  cout << "ANSWER: " << ans << endl << "-----------------" << endl;

/*
  cout << "-----------------" << endl
       << "Two-dimensional integral" << endl;

  double x0 = sqrt((sqrt(5)-1)/2);
  double int_dx_dy = 4 * (x0 * x0 * x0 / 3 + 0.5 * (1/sin(1.) - sqrt(1 - x0 * x0) * x0 - 1/sin(x0)));

  cout << "Integral (dx dy) = " << int_dx_dy << endl;

  double a = min(0., int_dx_dy), b = max(0., int_dx_dy);  // Uniform Distribution Parameters;

  UniformDistribution ud(a, b);
  ans = 0;
  for (int i = 0; i < N; i++) {
    double x = ud.Next();
    double y = ud.Next();
    ans += (b - a) / (x * x + y * y);
  }
  ans /= N;
  cout << "ANSWER: " << ans << endl << "-----------------" << endl; */

  return 0;
}
