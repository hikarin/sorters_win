#include "stdafx.h"
#include "quick.h"


Quick::Quick(std::vector<Bignum> v)
	: Sort(v)
{}

void Quick::execute()
{
	quicksort(0, elements.size() - 1);
}

Bignum Quick::partition(Bignum start, Bignum end)
{
	Bignum pivot = elements[(start+end)/2];
	Bignum i = start - 1;
	Bignum j = end + 1;

	while (true)
	{
		do { i++; } while (elements[i] < pivot);
		do { j--; } while (elements[j] > pivot);

		if (i >= j) {
			return j;
		}

		swap(elements[i], elements[j]);
	}
}

void Quick::quicksort(Bignum start, Bignum end)
{
	if (start < end)
	{
		Bignum p = partition(start, end);
		quicksort(start, p);
		quicksort(p+1, end);
	}
}