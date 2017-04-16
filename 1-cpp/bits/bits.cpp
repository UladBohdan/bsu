#include "bits.h"

void bits::push(int a)
{
	if (!find(a))
	{
		int arr=0, pos=a;
		while (pos>63)
		{
			arr++;
			pos-=64;
		}
		unsigned long int temp=1;
		temp=temp<<(63-pos);
		data[arr]+=temp;
	}
}

void bits::pop(int a)
{
	if (find(a))
	{
		int arr=0, pos=a;
		while (pos>63)
		{
			arr++;
			pos-=64;
		}
		unsigned long int temp=1;
		temp=temp<<(63-pos);
		data[arr]-=temp;
	}
}

bool bits::find(int a)
{
	int arr=0, pos=a;
	while (pos>63)
	{
		arr++;
		pos-=64;
	}
	unsigned long int temp=data[arr];
	temp=temp>>(63-pos);
	return (temp%2==1 ? true : false);
}

int* bits::out()
{
	vector <int> values;
	unsigned long int temp[4];
	temp[0]=data[0];
	temp[1]=data[1];
	temp[2]=data[2];
	temp[3]=data[3];
	for (int k=0; k<4; k++)
	{
		int pos=63;
		while (temp[k]!=0 && pos>=0)
		{
			if (temp[k]%2==1)
				values.push_back(pos+k*64);
			temp[k]>>=1;
			pos--;
		}
	}
	sort(values.begin(),values.end());
	int* ans = new int[values.size()+1];
	for (unsigned int i=0; i<values.size(); i++)
		ans[i]=values[i];
	ans[values.size()]=-1;
	return ans;
}
