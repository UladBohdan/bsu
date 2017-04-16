#include <iostream>

using namespace std;

class complex
{
	private:
	public:
		double re, im;
		complex() : re(0), im(0)
		{}
		complex(double a) : re(a), im(0)
		{}
		complex(double a, double b) : re(a), im(b)
		{}
		complex (complex& a) : re(a.re), im(a.im)
		{}
		void show();
		complex operator+ (complex a);
		complex operator- (complex a);
		void operator= (complex& a);
		void operator= (double a);
		bool operator> (complex a);
		bool operator< (complex a);
		bool operator== (complex a);
		~complex()
		{}
};
