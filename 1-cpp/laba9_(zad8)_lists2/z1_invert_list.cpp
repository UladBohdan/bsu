#include <iostream>
#include "singly_linked_list.h"
#include <stack>

using namespace std;

class singly_linked_list;

class list_invert : public singly_linked_list
{
	public:
		void invert();
};

void list_invert::invert()
{
	link* temp = begin();
	stack <int> st;
	while (temp)
	{
		st.push(temp->data);
		temp=temp->next;
	}
	temp=begin();
	while (temp)
	{
		temp->data=st.top();
		st.pop();
		temp=temp->next;
	}
}

int main()
{
	int n, k;
	list_invert a;
	cout << "Enter the size of the list: ";
	cin >> n;
	cout << "Enter your list: ";
	for (int i=0; i<n; i++)
	{
		cin >> k;
		a.push_back(k);
	}
	cout << "Your list: ";
	a.show();
	cout << "Inverted list: ";
	a.invert();
	a.show();
	return 0;
}
