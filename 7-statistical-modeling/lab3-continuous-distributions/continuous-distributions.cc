#include <iostream>

#include "../common/continuous.cc"

using namespace std;

int main() {
  srand(time(NULL));

  try {
    cout << "---------- RUN Uniform Distribution ----------" << endl;
    UniformDistribution(2, 4).RunTests();
    cout << endl;

    cout << "---------- RUN Standart Normal Distribution ----------" << endl;
    StandartNormalDistribution().RunTests();
    cout << endl;

    cout << "---------- RUN Exponential Distribution ----------" << endl;
    ExponentialDistribution(0.5).RunTests();
    cout << endl;

    cout << "---------- RUN Laplace Distribution ----------" << endl;
    LaplaceDistribution(0.5).RunTests(30000);
    cout << endl;

    cout << "---------- RUN Logistic Distribution ----------" << endl;
    LogisticDistribution(5, 2).RunTests(30000);
    cout << endl;

  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}
