#include <iostream>
#include <time.h>

#include "../common/base.cc"

using namespace std;

const int INIT_VALUE = 4099;

int main() {
  srand(time(NULL));

  cout << "---------- RUN Standart C++ Random ----------" << endl;
  StandartRandomGenerator().RunTests();
  cout << endl;

  cout << "---------- RUN Multiplicative Congruential Generator ----------" << endl;
  MultiplicativeCongruentialGenerator(INIT_VALUE, INIT_VALUE, 2147483647).RunTests();
  cout << endl;

  cout << "---------- RUN Running MacLaren-Marsaglia Generator ----------" << endl;
  MacLarenMarsagliaGenerator(20000).RunTests();
  cout << endl;
}
