#include "stdafx.h"
#include "afx.h"

#pragma once

class Item : public CObject
{
public:
	DECLARE_SERIAL(Item)
	Item() : sur(""), depart(""), sal(0) { }
	Item(CString s1, CString s2, int n) : sur(s1), depart(s2), sal(n) { }
	Item (const Item &p) : sur(p.sur), depart(p.depart), sal(p.sal) { }
	Item& operator= (const Item &p);
	virtual ~Item() { }
	void Serialize(CArchive&);
	CString str();
	CString sur, depart;
	int sal;
};