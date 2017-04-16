#include <iostream>
#include <cmath>

using namespace std;

int main() 
{
	double x=1, const1=1, const2=2, const4=4;
	double cur=0, sum=0;
	__asm	{
		mov ecx, 400
loop1:
		finit
		fld const1
		fld const4
		fld x
		fld x
		fmul st(0), st(1)
		fmul st(0), st(2)
		fsub st(0), st(3)
		fmul st(0), st(1)
		fdiv st(3), st(0)
		fxch st(3)
		fstp cur
		finit
		fld const1
		fld x
		fadd st(0), st(1)
		fstp x
		fld cur
		fld sum
		fadd st(0), st(1)
		fstp sum
		loop loop1
		fld sum
		fadd const1
		fdiv const2
		fstp sum
		}
	cout << "ln2:" << endl;
	cout << "cmath: " << log(2.) << endl;
	cout << "our:   " << sum << endl;
	return 0;
}