#pragma once
#include "sort.h"
class Comb :
	public Sort
{
public:
	Comb(std::vector<Bignum> v);
	virtual ~Comb() {};
	
	void execute() override;
};

