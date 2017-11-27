#include <iostream>

#include "../common/base.cc"

using namespace std;

const int INIT_VALUE = 4099;

int main() {
  cout << "|||||||| Standart C++ Random ||||||||" << endl;
  StandartRandomGenerator().RunTests();
  cout << endl;

  cout << "|||||||| Multiplicative Congruential Generator ||||||||" << endl;
  MultiplicativeCongruentialGenerator(INIT_VALUE, INIT_VALUE, 2147483647).RunTests();
  cout << endl;

  cout << "|||||||| Running MacLaren-Marsaglia Generator ||||||||" << endl;
  MacLarenMarsagliaGenerator(20000).RunTests();
  cout << endl;
}
