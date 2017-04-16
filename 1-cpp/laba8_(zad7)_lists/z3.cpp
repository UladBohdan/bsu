//3. N серых и M белых мышей сидят по кругу. Кошка ходит по кругу по часовой стрелке и съедает каждую s-ую мышку. 
//В первый раз счет начинается с серой мышки. Составьте алгоритм, определяющий порядок, в котором сидели мышки, 
//если через некоторое время осталось K серых и L белых мышей. В решении использовать структуру данных «список».

#include <iostream>
#include "cyclic_singly_linked_list.h"

using namespace std;

class cyclic_singly_linked_list;

class list_mouses : public cyclic_singly_linked_list
{
	public:
		void go_by_s(int, int, int);
		void add_colors(int, int, int, int);
		void show_colors();
};

void list_mouses::go_by_s(int s, int k, int l)
{
	link* temp=start;
	do 
		temp=temp->next;
	while (temp->next!=start);
	int t=0;
	while (t<sz-k-l)
	{
		cout << "done" << t << endl;
		show();
		for (int i=0; i<s-1; i++)
		{
			do
				temp=temp->next;
			while (temp->data!=1);
		}
		temp->next->data=2;
		t++;
	}
}

void list_mouses::add_colors(int gr_al, int wh_al, int gr_dead, int wh_dead)
{
	link* temp=start;
	for (int i=0; i<sz; i++)
	{
		// 1 - alive, 2 - dead
		// 3 - grey, 4 = white
		if (temp->data==1)
		{
			if (wh_al>0)
			{
				temp->data=4;
				wh_al--;
			}
			else
				temp->data=3;
		}
		else
		{
			if (wh_dead>0)
			{
				temp->data=4;
				wh_dead--;
			}
			else
				temp->data=3;
		}
		temp=temp->next;
	}
}

void list_mouses::show_colors()
{
	link* temp=start;
	do
	{
		temp->data==3 ? cout << "G " : cout << "W ";
		temp=temp->next;
	}
	while (temp!=start);
	cout << endl;
} 

int main()
{
	int n, m, k, l, s;
	cout << "Enter N (number of gray), M (number of white), S, K (the rest of gray), L (the rest of white): ";
	cin >> n >> m >> s >> k >> l;
	list_mouses ab;
	for (int i=0; i<n+m; i++)
		ab.push_front(1);
	ab.go_by_s(s, k, l);
	cout << "1st: "; ab.show();
	ab.add_colors(k,l,n-k,m-l);
	cout << "2nd: "; ab.show();
	ab.show_colors();
	return 0;
}
