#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "../common/discrete.cc"

const int N = 200;  // Chain length.
const int L = 10000;  // Number of chaines generated.

using namespace std;

int main() {
  srand(time(NULL));
  cout << "Solving System of Linear Equations with Monte-Carlo method." << endl;

  BernoulliDistribution bd(0.5);
  // bd.RunTests();

  // Data.
  double A[2][2];
  A[0][0] = 0.7;  A[0][1] = 0.1;
  A[1][0] = 0.5;  A[1][1] = -0.1;
  double f[2] = {-3, 0.2};

  double pi[2] = {0.5, 0.5};
  double P[2][2];
  P[0][0] = 0.5;
  P[0][1] = 0.5;
  P[1][0] = 0.5;
  P[1][1] = 0.5;

  for (int h_vers = 0; h_vers < 2; h_vers++) {
    double h[2];
    if (h_vers == 0) {
      h[0] = 1.;
      h[1] = 0.;
    } else {
      h[0] = 0.;
      h[1] = 1.;
    }

    double ans = 0;

    // Modelling L random variables and averaging them.
    vector<int> chain(N);  // Markov chain.
    vector<double> Q(N);  // Wages.
    for (int l = 0; l < L; l++) {
      double ksi = 0;

      for (int i = 0; i < N; i++) {
        chain[i] = (int)bd.Next();
      }

      int i0 = chain[0];
      Q[0] = (pi[i0] == 0 ? 0 : h[i0] / pi[i0]);
      for (int i = 1; i < N; i++) {
        int ik = chain[i];
        int ik_prev = chain[i-1];
        Q[i] = Q[i-1] * (P[ik_prev][ik] == 0 ? 0 : A[ik_prev][ik] / P[ik_prev][ik]);
      }

      for (int i = 0; i < N; i++) {
        ksi += Q[i] * f[chain[i]];
      }

      ans += ksi;
    }
    ans /= L;
    cout << (h_vers == 0 ? "X: " : "Y: ") << ans << endl;
  }
}
