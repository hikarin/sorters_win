#include "stdafx.h"
#include "Comb.h"


Comb::Comb(std::vector<Bignum> v)
	: Sort(v)
{
}

void Comb::execute()
{
	const Bignum size = elements.size();
	Bignum h = size / 2;
	bool bChanged = false;
	while (h>=1)
	{
		bChanged = false;
		for (Bignum i = 0; i < size; i++)
		{
			if(i+h >= size)
			{
				break;
			}
			if (elements[i] > elements[i+h])
			{
				swap(elements[i], elements[i + h]);
				bChanged = true;
			}
		}

		if (h == 1 && bChanged)
		{
			continue;
		}

		h = (Bignum)((float)h / 1.3f);
	}
}