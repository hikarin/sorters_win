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
	static void CALLBACK bitonic_sub(PTP_CALLBACK_INSTANCE Instance, PVOID Param, PTP_WORK Work);
	int threadNum;
};

