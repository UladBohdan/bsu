#ifndef COMMON_TEST_CPP_
#define COMMON_TEST_CPP_

#include "test.h"

void MomentsTest(const vector<double>& x) {
  int n = x.size();

  double m = 0;
  for (int i = 0; i < n; i++) {
    m += x[i];
  }
  m /= n;
  cout << "Expectation: " << m << endl;
  double s2 = 0;
  for (int i = 0; i < n; i++) {
    s2 += (x[i] - m) * (x[i] - m);
  }
  s2 /= (n - 1);
  cout << "S2: " << s2 << endl;

  cout << "math expectation test... " <<
    (abs(m - 0.5) < EPS ? "passed." : "failed.") << endl;
  cout << "dispersion test..." <<
    (abs(s2 - 1./12) < EPS ? "passed." : "failed.") << endl;
}

void PearsonTest(const vector<double>& x) {
  // p_k = 0.1 for each k = [0, 9];
  int n = x.size();
  vector<double> v(10);
  for (int i = 0; i < n; i++) {
    int gr = int(x[i] * 10);
    if (gr == 10) {
      gr = 9;
    }
    v[gr] += 1.;
  }
  double hi2 = 0;
  for (int i = 0; i < 10; i++) {
    hi2 += ((v[i] - n * 0.1) * (v[i] - n * 0.1) * 1. / (n * 0.1));
  }
  cout << "Pearson test... ";
  if (hi2 < PEARSON_THRESHOLD){
    cout << "passed." << endl;
  } else {
    cout << "failed with value " << hi2 << endl;
  }
}

void KolmogorovTest(const vector<double>& x) {
  int n = x.size();
  double mx = 0;
  vector<double> v(x.begin(), x.end());
  sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++) {
    mx = max(mx, (i * 1. / n) - v[i]);
  }
  cout << "Kolmogorov test... ";
  mx *= sqrt(n);
  if (mx < KOLMOGOROV_THRESHOLD) {
    cout << "passed." << endl;
  } else {
    cout << "failed with value " << mx << endl;
  }
}

#endif  // COMMON_TEST_CPP_
