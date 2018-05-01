#pragma once
#include "sort.h"
#include <Windows.h>
#include <process.h>

class Bitonic : public Sort
{
public:
	Bitonic(std::vector<Bignum> v, int num);
	virtual ~Bitonic() {};

	void execute() override;

private:	
	static void bitonic_sub(std::vector<Bignum>& vec, Bignum start, Bignum end, Bignum block, Bignum step);
	int threadNum;
};