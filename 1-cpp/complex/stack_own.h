#include <iostream>
#include "complex.h"

using namespace std;

class stack_own
{
	struct elem
	{
		complex data;
		elem* next;
	};
	private:
		elem* place;
		int sz;
	public:
		stack_own() : place(NULL), sz(0)
		{}
		int size();
		bool empty();
		void push(complex);
		complex top();
		void pop();
		~stack_own();
};
