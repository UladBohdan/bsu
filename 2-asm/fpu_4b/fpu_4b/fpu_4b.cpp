#include <iostream>

using namespace std;

int main()
{
	double x, ans, fulldeg, z;
	double c10=10, half=0.5;
	cout << "degree: ";
	cin >> x;
	__asm {
		finit
		fld x
		fld c10
		fyl2x
		fst fulldeg
		
		finit
		fld fulldeg
		fsub half
		frndint
		fst z
		fld1
		fscale
		fst ans

		finit
		fld fulldeg
		fsub z
		f2xm1
		fld1
		fadd
		fld ans
		fmul
		fst ans
	}
	cout << "10^" << x << "=" << ans << endl;
	return 0;
}