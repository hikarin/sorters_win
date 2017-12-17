#include "stdafx.h"
#include "Bubble.h"


Bubble::Bubble(std::vector<Bignum> v)
	: Sort(v)
{
}

Bubble::~Bubble()
{
}

void Bubble::execute()
{
	const Bignum size = elements.size();;
	for (Bignum i = 0; i < size-1; i++)
	{
		bool bChanged = false;
		for (Bignum j = size-1; j>i; j--)
		{
			if (elements[j] < elements[j-1])
			{
				swap(elements[j], elements[j-1]);
				bChanged = true;
			}
		}

		if (!bChanged)
		{
			break;
		}
	}
}
