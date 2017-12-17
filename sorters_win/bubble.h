#pragma once
#include "sort.h"
class Bubble :
	public Sort
{
public:
	Bubble(std::vector<Bignum> v);
	virtual ~Bubble();

	void execute() override;
protected:

};

