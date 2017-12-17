#pragma once
#include "sort.h"
class Quick : public Sort
{
public:
	Quick(std::vector<Bignum> v);
	virtual ~Quick() {};

	void execute() override;
protected:
	Bignum partition(Bignum start, Bignum end);
	void quicksort(Bignum start, Bignum end);
};

