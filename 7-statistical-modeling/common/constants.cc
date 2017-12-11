#ifndef COMMON_CONSTANTS_CC_
#define COMMON_CONSTANTS_CC_

#include <unordered_map>

const int M = 100000007;
// EPS == 1 is not a good thing. This is to avoid some weird behaviour on
// Moments test for Continuous Distributions.
const double EPS = 1;
const double DEFAULT_PEARSON_THRESHOLD = 16.92;
const double KOLMOGOROV_THRESHOLD = 1.36;

const int DEFAULT_TEST_SIZE = 10000;

const std::string COLOUR_GREEN = "\033[1;32m";
const std::string COLOUR_RED = "\033[1;31m";
const std::string COLOUR_DEFAULT = "\033[0m";

const int TEST_NAME_OUTPUT_WIDTH = 20;

// Xi2 values.
std::unordered_map<int, double> XI_VALUES = {
  {  2, 3.8415 },
  {  8, 14.067 },
  { 11, 18.307 },
  { 20, 30.144 },
  { 21, 31.41  },
};

#endif  // COMMON_CONSTANTS_CC_
