#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <utility>

using namespace std;

class Animal
{
	public:
		string type;
		int age;
		list<string> feed;
};

bool sortlist (Animal a, Animal b)
{
	return (a.type<b.type || (a.type==b.type && a.age<b.age));
}

bool remage (Animal a)
{
	return (a.age==2);
}

bool sortpairs (pair<int,string> a, pair<int,string> b)
{
	return a.second<b.second;
}

int main()
{
	ifstream fin("animals_bohdan");
	vector <Animal> v;
	string temp;
	Animal t;
	bool first=true;
	while (!fin.eof())
	{
		fin >> temp;
		if (temp=="cat" || temp=="dog" || temp=="hamster")
		{
			if (!first)
				v.push_back(t);
			t.feed.clear();
			first=false;
			t.type=temp;
		}	
		else if (temp[0]<=57)
		{
			int x=0;
			for (unsigned int i=0; i<temp.length(); i++)
				x=x*10+temp[i]-48;
			t.age=x;
		}
		else
		{
			t.feed.push_back(temp);
		}
	}
	t.feed.pop_back();
	v.push_back(t);
	
	cout << "OUR ANIMALS:" << endl;
	for (vector<Animal>::iterator it=v.begin(); it!=v.end(); it++)
	{
		cout << "  " << setw(7) << it->type << " " << setw(2) << it->age << "  ";
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			cout << *jt << " ";
		cout << endl;
	}
	
	list<Animal> l(v.begin(),v.end());
	l.sort(sortlist);
	cout << endl << "SORTED LIST OF ANIMALS:" << endl;
	for (list<Animal>::iterator it=l.begin(); it!=l.end(); it++)
	{
		cout << "  " << setw(7) << it->type << " " << setw(2) << it->age << "  ";
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			cout << *jt << " ";
		cout << endl;
	}
	
	v.resize(remove_if(v.begin(),v.end(),remage)-v.begin());	// Removing and resizing
	cout << endl << "VECTOR WITHOUT ANIMALS WITH AGE 2:" << endl;
	for (vector<Animal>::iterator it=v.begin(); it!=v.end(); it++)
	{
		cout << "  " << setw(7) << it->type << " " << setw(2) << it->age << "  ";
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			cout << *jt << " ";
		cout << endl;
	}
	
	for (vector<Animal>::iterator it=v.begin(); it!=v.end(); it++)
	{
		// Replace_if does not work with list
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			if (*jt=="meat")
				(*jt)="new_feed";
	}
	cout << endl << "REPLACING ALL meat WITH new_feed. NEW VECTOR:" << endl;
	for (vector<Animal>::iterator it=v.begin(); it!=v.end(); it++)
	{
		cout << "  " << setw(7) << it->type << " " << setw(2) << it->age << "  ";
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			cout << *jt << " ";
		cout << endl;
	}
	
	map < string, stack<int> > m;
	for (list<Animal>::iterator it=l.begin(); it!=l.end(); it++)
	{
		if (it->type=="dog")
			for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
				m[*jt].push(it->age);
	}
	cout << endl << "EACH FEED AND APPROPRIATE DOGS (their ages):" << endl;
	for (map<string,stack<int> >::iterator it=m.begin(); it!=m.end(); it++)
	{
		cout << "  " << it->first << " :  ";
		while (!it->second.empty())
		{
			cout << it->second.top() << " ";
			it->second.pop();
		}
		cout << endl;
	}
	
	deque < pair<int,string> > f;
	for (list<Animal>::iterator it=l.begin(); it!=l.end(); it++)
		for (list<string>::iterator jt=it->feed.begin(); jt!=it->feed.end(); jt++)
			f.push_back(make_pair(1,*jt));
	sort(f.begin(),f.end(),sortpairs);
	for (deque<pair<int,string> >::iterator it=f.begin(); it!=f.end(); it++)
	{
		while (it+1<f.end() && (it+1)->second==it->second)
		{
			it->first++;
			f.erase(it+1);
		}
	}
	sort(f.begin(),f.end());
	cout << endl << "THE RAREST FEED(s) - just for " << f.begin()->first << " animal(s):" << endl << "  ";
	for (deque<pair<int,string> >::iterator it=f.begin(); it!=f.end(); it++)
		if (it->first==f.begin()->first)
			cout << it->second << " ";
			
	cout << endl << endl << "Have a nice day!";
	return 0;
}
