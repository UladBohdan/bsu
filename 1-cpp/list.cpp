//Class list
//Signly linked list

#include <iostream>

using namespace std;

class list
{
	struct link
	{
		int data;
		link *next;
	};
	private:
		int sz;
		link* start;
	public:
		list() : sz(0), start(NULL)
		{  }
		int size()	{ return sz; }
		void push_front(int x);
		void push_back(int x);
		void pop_front();
		void pop_back();
		void show();
		void sort();
		~list();
};

void list::push_back(int x)
{
	link* temp = start;
	while (temp->next)
		temp=temp->next;
	link* temp2 = new link;
	temp2->data=x;
	temp2->next=NULL;
	temp->next=temp2;
	sz++;
}

void list::push_front(int x)
{
	link* temp = new link;
	temp->data=x;
	temp->next=start;
	start=temp;
	sz++;
}

void list::pop_front()
{
	delete start;
	start=start->next;
	sz--;
}

void list::pop_back()
{
	link* temp = start;
	while (temp->next->next)
		temp=temp->next;
	delete temp->next;
	temp->next=NULL;
	sz--;
}

void list::show()
{
	link* temp = start;
	while (temp)
	{
		cout << temp->data << " ";
		temp=temp->next;
	}	
	cout << endl;
}

void list::sort()
{
	link* fixed = start;
	link* temp;
	link* mn;
	while (fixed->next)
	{
		temp=fixed->next;
		mn=fixed;
		while (temp)
		{
			if ((temp->data) < (mn->data))
				mn=temp;
			temp=temp->next;
		}
		swap(mn->data, fixed->data);
		fixed=fixed->next;
	}
}

list::~list()
{
	link* temp = start;
	while (temp)
	{
		link* temp2 = temp;
		temp=temp->next;
		delete temp2;
	}
}

int main()
{
	list ab;
	ab.push_front(7);
	ab.push_front(8);
	ab.push_front(10);
	ab.show();
	ab.push_back(13);
	ab.pop_front();
	ab.show();
	ab.pop_back();
	ab.push_back(56);
	ab.push_back(10);
	ab.push_back(-5);
	ab.push_front(17);
	ab.push_front(3);
	ab.show();
	ab.sort();
	ab.show();
	return 0;
}
