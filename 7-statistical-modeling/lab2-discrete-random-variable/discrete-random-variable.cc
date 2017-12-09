#include <iostream>

#include "../common/discrete.cc"

using namespace std;

int main() {
  srand(time(NULL));

  try {
    cout << "|||||||| Bernoulli Distribution ||||||||" << endl;
    BernoulliDistribution(0.2).RunTests();
    cout << endl;

    cout << "|||||||| Binomial Distribution ||||||||" << endl;
    BinomialDistribution(5, 0.2).RunTests();
    cout << endl;
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}
