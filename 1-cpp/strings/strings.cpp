#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <cstdio>

using namespace std;

class str
{
	protected:
		char* data;
		int sz;
	public:
		str() : sz(0)
		{
			data=NULL;
		}
		str(char a) : sz(1)
		{
			char *temp = new char[1];
			temp[0]=a;
			data=temp;
		} 
		str(char* a) : sz(strlen(a))
		{
			char *temp = new char[strlen(a)];
			strcpy(temp,a);
			data=temp;
		}
		str(str& a) : data(a.data) , sz(a.sz) { }
	    void clear()
		{
			if (sz>0)
			{
				delete[] data;
				data=NULL;
				sz=0;
			}
		} 
		void operator= (str &a)
		{
			char *temp = new char[strlen(a.data)];
			strcpy(temp,a.data);
			data=temp;
			sz=strlen(a.data);
		} 
		void operator+= (str &a)
		{
			char *temp = new char[a.sz+sz];
			for (int i=0; i<sz; i++)
				temp[i]=data[i];
			int pos=sz;
			for (int i=0; i<a.sz; i++, pos++)
				temp[pos]=a.data[i];
			data=temp;
			sz+=a.sz;
		} 
		virtual bool les (str &a) 
		{ 
			int mn=min(sz,a.sz);
			for (int i=0; i<mn; i++)
				if (data[i]!=a.data[i])
					return (data[i]<a.data[i] ? true : false);
			return (sz==mn ? true : false);
		}
		bool operator< (str &a) { return les(a); }
		bool operator== (str &a)
		{
			if (a.sz!=sz)
				return false;
			else
			{
				for (int i=0; i<sz; i++)
					if (data[i]!=a.data[i])
						return false;
				return true;
			}
		}
		bool operator> (str &a)
		{
			int mn=min(sz,a.sz);
			for (int i=0; i<mn; i++)
				if (data[i]!=a.data[i])
					return (data[i]>a.data[i] ? true : false);
			return (sz==mn ? false : true);
		}
		virtual int type() { return 1; }
		virtual void show()
		{
			for (int i=0; i<sz; i++)
				cout << data[i];
			cout << endl;
		}
		void show_full()
		{
			for (int i=0; i<sz; i++)
				cout << data[i];
			cout << "   (size " << sz << ")" << endl;
		}
		virtual int length() { return sz; }
		int str_int()
		{
			int temp=0;
			for (int i=0; i<sz; i++)
				temp=temp*10+data[i]-48;
			return temp;
		}
		virtual operator int() { return 0; }
		~str() 
		{
			if (sz>0)
				delete[] data;
		}
		
};

class str10 : public str
{
	private:
		int val;
	public:
		str10()	: str() , val(str_int()) { }
		str10 (int b) :	str(int_str(b)), val(b) { }
		str10 (char s) : str(s) , val(str_int()) { }
		str10 (char* s) : str(s) , val(str_int()) { }
		str10 (str10 &a) : val(a.val) 
		{
			data=a.data;
			sz=a.sz;
		}
		str10 (str &a) : str(a) , val(str_int()) { }
		char* int_str(int b)
		{
			stack <int> temp;
			while (b>0)
			{
				temp.push(b%10);
				b/=10;
			}
			char* s = new char[temp.size()];
			int pos=0;
			while (!temp.empty())
			{
				s[pos]=temp.top()+48;
				temp.pop();
				pos++;
			}
			s[pos]='\0';
			return s;
		}
		virtual void show() { cout << val << endl; }
		virtual int length() { return sz; }
		virtual int type() { return 2; }
		bool operator== (str10 &a) { return (val==a.val); }
		bool operator> (str10 &a) { return (val>a.val); }
		virtual bool les (str &a) { return (val<a.str_int()); }
		bool operator< (str10 &a) { return (val<a.val); }
		operator int() { return val; }
		str10 operator+ (str10 a) { return str10(val+a.val); }
		void operator+= (str10 &a) { val+=a.val; data=int_str(val); sz=strlen(data); }
		void operator= (str10 &a)
		{
			char *temp = new char[strlen(a.data)];
			strcpy(temp,a.data);
			data=temp;
			sz=strlen(a.data);
			val=a.val;
		}
		int value() { return val; }
};

int main()
{
	cout << "EXAMPLES OF USING:" << endl;
	char s[]="hello";
	str a1('v'), a4(s), a3((char*)"abc");
	str a2;
	a2=a3;
	a1.show_full();
	a2.show_full();
	a3.show_full();
	a4.show_full();
	a3+=a4;
	a3.show_full();
	str10 b1((char*)"7654"), b2, b3(564);
	b1.show();
	b2.show();
	b3.show();
	cout << "len: " << b1.length() << " "; b1.show();
	cout << "len: " << b2.length() << " "; b2.show();
	cout << "len: " << b3.length() << " "; b3.show();
	int x=b3;
	if (x<b1)
		cout << "TRUE";
	else
		cout << "FALSE";
	cout << endl;
	str10 b4=b1+b3;
	cout << "!!:" << endl;
	b4.show();
	b2=b3;
	b2.show();
	b2+=b3;
	b2.show();
	
	str* p[]={&a1,&b3,&b1,&a4,&b4,&a3,&a2,&b2};
	vector <str*> t[2];
	for (int i=0; i<8; i++)
		t[p[i]->type()-1].push_back(p[i]);
	// Sorting strings and numbers...
	for (int k=0; k<2; k++)
	{
		for (unsigned int i=0; i<t[k].size()-1; i++)
		{
			int mn=i;
			for (unsigned int j=i+1; j<t[k].size(); j++)
				if (t[k][j]->les(*t[k][mn]))
					mn=j;
			swap(t[k][i], t[k][mn]);
		}
	}	
	str ans1;
	int ans2=0;
	cout << endl;
	cout << "   Sorted arrays:" << endl;
	cout << "  Strings: " << endl;
	for (unsigned int i=0; i<t[0].size(); i++)
		t[0][i]->show();
	for (int i=(t[0].size()-1); i>=0; i--)
		ans1+=(*t[0][i]);
	cout << "Connected string: ";
	ans1.show();
	cout << endl;
	cout << "  Numbers: " << endl;
	for (unsigned int i=0; i<t[1].size(); i++)
	{
		t[1][i]->show();
		ans2+=((int)*t[1][i]);
	}
	cout << "Sum: " << ans2 << endl;
	return 0;
}
