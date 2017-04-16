#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct SStud 
{
	string name, subject;
	int mark;
};

bool subjsort(SStud a, SStud b)
{
	return (a.subject<b.subject || (a.subject==b.subject && a.name<b.name));
}

bool unsbj(SStud a, SStud b)
{
	return a.subject==b.subject;
}

bool howcopy(SStud a)
{
	return (a.name[0]!='H');
}

int main()
{
	ifstream fin("students");
	list <SStud> l;
	while (!fin.eof())
	{
		SStud temp;
		fin >> temp.name >> temp.subject >> temp.mark;
		l.push_back(temp);
	}
	l.pop_back();
	cout << "LIST OF STUDENTS:" << endl;
	for (list<SStud>::iterator i=l.begin(); i!=l.end(); i++)
		cout << i->name << " " << i->subject << " " << i->mark << endl;
	vector <SStud> v;
	for (list<SStud>::iterator i=l.begin(); i!=l.end(); i++)
		v.push_back(*i);
	sort(v.begin(),v.end(),subjsort);
	cout << endl << "STUDENTS SORTED BY SUBJECT" << endl;
	for (vector<SStud>::iterator i=v.begin(); i!=v.end(); i++)
		cout << i->name << " " << i->subject << " " << i->mark << endl;
	cout << endl << "ENTER A SUBJECT: ";
	string subj;
	cin >> subj;
	cout << "STUDENTS WHO PASSED " << subj << ":" << endl;
	int sum=0, num=0;
	for (unsigned int i=0; i<v.size(); i++)
	{
		if (v[i].subject==subj)
		{
			num++;
			sum+=v[i].mark;
			cout << "  " << v[i].name << endl;
		}
	}
	if (num==0)
		cout << "Nobody passed exams on " << subj << ":(" << endl;
	else
		cout << "Average mark: " << sum*1./num << endl;
	vector <SStud> uniqsubj (5);
	vector<SStud>::iterator it;
	it=unique_copy(v.begin(),v.end(),uniqsubj.begin(),unsbj);
	uniqsubj.resize(it-uniqsubj.begin());
	cout << endl << "LIST OF UNIQUE SUBJECTS (way 1):" << endl;
	for (vector<SStud>::iterator i=uniqsubj.begin(); i!=uniqsubj.end(); i++)
		cout << "  " << i->subject << endl;
	string* arr = new string[v.size()];
	for (unsigned int i=0; i<v.size(); i++)
		arr[i]=v[i].subject;
	set <string> s (arr,arr+v.size());
	cout << endl << "LIST OF UNIQUE SUBJECTS (way 2):" << endl;
	for (set<string>::iterator i=s.begin(); i!=s.end(); i++)
		cout << "  " << *i << endl;
	vector <SStud> v2 (10);
	it=remove_copy_if(v.begin(),v.end(),v2.begin(),howcopy);
	v2.resize(it-v2.begin());
	cout << endl << "VECTOR WITH SEVERAL STUDENTS:" << endl;
	for (unsigned int i=0; i<v2.size(); i++)
		cout << "  " << v2[i].name << " " << v2[i].subject << " " << v2[i].mark << endl;
	return 0;
}
