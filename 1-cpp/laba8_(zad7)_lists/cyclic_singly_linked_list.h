//Class Cyclic Signly Linked list

#include <iostream>

using namespace std;

struct link
{
	int data;
	link *next;
};

class cyclic_singly_linked_list
{
	protected:
		int sz;
		link* start;
		void remove(link*);
	public:
		cyclic_singly_linked_list() : sz(0), start(NULL)
		{  }
		int size()	{ return sz; }
		void push_front(int x);
		void push_back(int x);
		void pop_front();
		void pop_back();
		void show();
		void make_less (int k);
		~cyclic_singly_linked_list();
};

void cyclic_singly_linked_list::push_back(int x)
{
	if (sz==0)
	{
		push_front(x);
		return;
	}
	link* temp = start;
	while (temp->next!=start)
		temp=temp->next;
	link* temp2 = new link;
	temp2->data=x;
	temp2->next=start;
	temp->next=temp2;
	sz++;
}

void cyclic_singly_linked_list::push_front(int x)
{
	link* temp = new link;
	temp->data=x;
	if (sz==0)
		temp->next=temp;
	else
	{
		temp->next=start;
		link* tmp = start;
		while (tmp->next!=start)
			tmp=tmp->next;
		tmp->next=temp;
	}
	start=temp;
	sz++;
}

void cyclic_singly_linked_list::pop_front()
{
	
	link* tmp = start;
	while (tmp->next!=start)
		tmp=tmp->next;
	remove(tmp);
}

void cyclic_singly_linked_list::pop_back()
{
	link* tmp = start;
	while (tmp->next->next!=start)
		tmp=tmp->next;
	remove(tmp);
}

void cyclic_singly_linked_list::show()
{
	if (sz==0)
		cout << "EMPTY LIST:(" << endl;
	else
	{
		link* temp = start;
		do
		{
			cout << temp->data << " ";
			temp=temp->next;
		}	
		while (temp!=start);
		cout << endl; 
	}
}

void cyclic_singly_linked_list::make_less (int k) // task2
{
	if (k==0)
	{
		while (sz>0)
			remove(start);
		return;
	}
	int temp=1;
	link* prev = start;
	while (prev->next!=start)
		prev=prev->next;
	while (sz>k)
	{
		if (temp<k+1)
		{
			temp++;
			prev=prev->next;
		}
		else
		{
			remove(prev);
			temp=1;
		}
	}
}

void cyclic_singly_linked_list::remove(link* x)
{
	if (sz==1)
	{
		delete start;
		start=NULL;
	}
	else if (sz==2)
	{
		delete x->next;
		x->next=x;
	}
	else
	{
		if (x->next==start)
			start=x->next->next;
		link* temp = x->next->next;
		delete x->next;
		x->next=temp;
	}
	sz--;
}

cyclic_singly_linked_list::~cyclic_singly_linked_list()
{
	if (sz!=0)
	{
		link* temp = start;
		while (temp->next!=start)
		{
			link* temp2 = temp;
			temp=temp->next;
			delete temp2;
		}
	}
}
