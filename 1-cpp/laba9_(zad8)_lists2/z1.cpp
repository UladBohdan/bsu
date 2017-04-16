#include <iostream>
#include <stack>

using namespace std;

struct link
{
	int data;
	link *next;
};

class singly_linked_list
{
	private:
		int sz;
		link* start;
	public:
		singly_linked_list() : sz(0), start(NULL)
		{  }
		link* begin() { return start; }
		int size()	{ return sz; } //Returns size of list
		void push_front(int x); //Add an element to front
		void push_back(int x); //Add an element to back
		void pop_front(); //Remove the front element
		void pop_back(); //Remove the back element
		void show(); //Show the list
		void sort(); //Sort the list (N^2)
		~singly_linked_list();
};

void singly_linked_list::push_back(int x)
{
	if (sz==0)
	{
		push_front(x);
		return;
	}
	link* temp = start;
	while (temp->next)
		temp=temp->next;
	link* temp2 = new link;
	temp2->data=x;
	temp2->next=NULL;
	temp->next=temp2;
	sz++;
}

void singly_linked_list::push_front(int x)
{
	link* temp = new link;
	temp->data=x;
	temp->next=start;
	start=temp;
	sz++;
}

void singly_linked_list::pop_front()
{
	delete start;
	start=start->next;
	sz--;
}

void singly_linked_list::pop_back()
{
	link* temp = start;
	while (temp->next->next)
		temp=temp->next;
	delete temp->next;
	temp->next=NULL;
	sz--;
}

void singly_linked_list::show()
{
	link* temp = start;
	while (temp)
	{
		cout << temp->data << " ";
		temp=temp->next;
	}	
	cout << endl;
}

void singly_linked_list::sort()
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

singly_linked_list::~singly_linked_list()
{
	link* temp = start;
	while (temp)
	{
		link* temp2 = temp;
		temp=temp->next;
		delete temp2;
	}
}



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