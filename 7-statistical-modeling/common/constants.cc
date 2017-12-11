using namespace std;

const int M = 100000007;
// EPS == 1 is not a good thing. This is to avoid some weird behaviour on
// Moments test for Continuous Distributions.
const double EPS = 1;
const double PEARSON_THRESHOLD = 16.92;
const double KOLMOGOROV_THRESHOLD = 1.36;

const int DEFAULT_TEST_SIZE = 10000;

const string COLOUR_GREEN = "\033[1;32m";
const string COLOUR_RED = "\033[1;31m";
const string COLOUR_DEFAULT = "\033[0m";

const int TEST_NAME_OUTPUT_WIDTH = 20;
