#include "complex.h"

void complex::show()
{
	if (im==0)
		cout << re;
	else if (im!=0)
	{
		if (re==0)
			cout << im << "i";
		else
			cout << re << "+" << im << "i";
	}
}

complex complex::operator+ (complex a)
{
	complex tmp;
	tmp.re=re+a.re;
	tmp.im=im+a.im;
	return tmp;
}

complex complex::operator- (complex a)
{
	complex tmp;
	tmp.re=re-a.re;
	tmp.im=im-a.im;
	return tmp;
}

void complex::operator= (complex& a)
{
	re=a.re;
	im=a.im;
}

void complex::operator= (double a)
{
	re=a;
	im=0;
}

bool complex::operator> (complex a)
{
	if (a.re*a.re+a.im*a.im<re*re+im*im)
		return true;
	else
		return false;
}

bool complex::operator< (complex a)
{
	if (a.re*a.re+a.im*a.im>re*re+im*im)
		return true;
	else
		return false;
}

bool complex::operator== (complex a)
{
	if (a.re==re && a.im==im)
		return true;
	else
		return false;
}
