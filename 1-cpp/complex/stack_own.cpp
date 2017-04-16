#include "stack_own.h"

int stack_own::size()
{
	return sz;
}

bool stack_own::empty()
{
	if (!sz)
		return true;
	else
		return false;
}

void stack_own::push(complex a)
{
	elem *tmp = new elem;
	tmp->data=a;
	tmp->next=place;
	place=tmp;
	sz++;
} 

complex stack_own::top()
{
	return place->data;
}

void stack_own::pop()
{
	if (!sz)
	{
		cout << "Error. Empty stack." << endl;
		return;
	}
	elem* temp=place;
	place=place->next;
	delete temp;
	sz--;	
}

stack_own::~stack_own()
{
	while (!empty())
		pop();
}
