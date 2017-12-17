#include "stdafx.h"
#include "sort.h"
#include <random>
#include <time.h>

Sort::Sort(std::vector<Bignum> v)
	: elements(v)
{}

Sort::~Sort()
{}

void Sort::init(std::vector<Bignum>& v)
{
	std::srand((unsigned int)time(nullptr));
	for (auto p = v.begin(); p != v.end(); p++)
	{
		*p = std::rand() % v.size();
	}
}

bool Sort::check() const
{
	for (auto p = elements.begin(); (p + 1) != elements.end(); p++)
	{
		if (*p > *(p + 1)) {
			return false;
		}
	}
	return true;
}