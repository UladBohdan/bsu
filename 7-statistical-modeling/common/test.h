#ifndef COMMON_TEST_H_
#define COMMON_TEST_H_

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const double EPS = 0.01;
const double PEARSON_THRESHOLD = 16.92;
const double KOLMOGOROV_THRESHOLD = 1.36;

void MomentsTest(const vector<double>&);

void PearsonTest(const vector<double>&);

void KolmogorovTest(const vector<double>&);

#endif  // COMMON_TEST_H_
