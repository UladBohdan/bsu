#include <iostream>

using namespace std;

int main() 
{
	double dif, cur=0, sum=0; 
	double const0=0, cur_x=0, n=1000;
	_asm {
		finit
		fld n
		fldpi
		fldpi
		fadd st(0), st(1)
		fdiv st(0), st(2)
		fstp dif
		mov ecx, 1000
		fld dif
		fld const0
		fld const0
loop1:
		fmul st(0), st(1)
		fxch st(1)
		fsin
		fadd st(0), st(1)
		fmul st(0), st(2)
		fstp cur
		finit
		fld cur
		fadd sum
		fstp sum
		finit
		fld cur_x
		fadd dif
		fst cur_x
		finit
		fld dif
		fld cur_x
		fld cur_x
		loop loop1
	}
	cout << "answer: " << sum << endl;
}