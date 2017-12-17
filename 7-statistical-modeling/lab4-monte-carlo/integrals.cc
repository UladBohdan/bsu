#include <cmath>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
  {
    int N = 8000;
    cout << "-----------------" << endl
         << "One-dimensional integral on [-inf, inf]: e^(-x^2)*sqrt(1+x^2)" << endl;

    default_random_engine generator;
    normal_distribution<double> n_distribution(0,1./sqrt(2));

    double ans = 0;
    for (int i = 0; i < N; i++) {
      double x = n_distribution(generator);
      ans += sqrt(M_PI * (1 + x * x));
    }
    ans /= N;
    cout << "ANSWER: " << ans << endl << "-----------------" << endl;


    cout << "-----------------" << endl << "Two-dimensional integral" << endl;
  }

  {
    int N = 1000000;
    double x0 = sqrt((sqrt(5)-1)/2);
    double int_dx_dy = 1.0086; // pre-calculated manually.

    default_random_engine generator;
    uniform_real_distribution<double> u_distribution(-1.0,1.0);

    long double ans = 0;
    int success_rate = 0;
    for (int i = 0; i < N; i++) {
      double x = u_distribution(generator);
      double y = u_distribution(generator);

      if (x*x+y*y <=1 && abs(y) <= x*x) {
        success_rate++;
        ans += 1 / (x*x+y*y);
      }
    }
    ans /= success_rate;
    // ans /= int_dx_dy;
    cout << "Success rate: " << success_rate*1. / N << endl;
    cout << "ANSWER: " << ans << endl << "-----------------" << endl;
  }

  return 0;
}
