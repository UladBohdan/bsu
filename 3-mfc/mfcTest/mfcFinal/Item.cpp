#include "stdafx.h"
#include "Item.h"

IMPLEMENT_SERIAL( Item, CObject, 1 )

Item& Item::operator= (const Item& p)
{
	sur=p.sur;
	depart=p.depart;
	sal=p.sal;
	return *this;
}

void Item::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
		ar << sur << depart << sal;
	else
		ar >> sur >> depart >> sal;
	return;
}

CString Item::str()
{
	char buf[300];
	sprintf(buf,"%s, %s       %d",sur,depart,sal);
	return (CString)buf;
}