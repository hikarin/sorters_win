#include "stdafx.h"
#include "bitonic.h"
#include <windows.h>

struct ThreadParam
{
	std::vector<Bignum>* pElement;
	Bignum block;
	Bignum step;
	Bignum start;
	Bignum end;
};

Bitonic::Bitonic(std::vector<Bignum> v, int num)
	: Sort(v)
{
	threadNum = num;
}

void Bitonic::execute()
{
	//	adjust vector size
	const Bignum prev_size = elements.size();
	Bignum new_size = prev_size;
	while ((new_size & (new_size - 1)) != 0)
	{
		elements.push_back(UINT_MAX);
		++new_size;
	}

	int stackSize = 0;
	ThreadParam* threadParam = new ThreadParam[threadNum];
	PTP_WORK* Work = new PTP_WORK[threadNum];

	Bignum range = new_size / threadNum;
	
	auto pool = CreateThreadpool(NULL);

	for (int i = 0; i < threadNum; i++)
	{
		threadParam[i].start = range * i;
		threadParam[i].end = min(new_size, range * (i + 1) - 1);
		threadParam[i].pElement = &elements;

		Work[i] = CreateThreadpoolWork(bitonic_sub, &threadParam[i], NULL);
	}

	for (Bignum block = 1; block <= new_size; block *= 2)
	{
		for (Bignum step = block / 2; step >= 1; step /= 2)
		{
			for (int i = 0; i < threadNum; i++)
			{
				threadParam[i].block = block;
				threadParam[i].step = step;
				
				SubmitThreadpoolWork(Work[i]);
			}

			for (int i = 0; i < threadNum; i++)
			{
				WaitForThreadpoolWorkCallbacks(Work[i], false);
			}
		}
	}

	for (int i=0; i<threadNum; i++)
	{
		CloseThreadpoolWork(Work[i]);
	}
	CloseThreadpool(pool);

	while (new_size > prev_size)
	{
		elements.pop_back();
		--new_size;
	}

	delete[] Work;
	delete[] threadParam;
}

void CALLBACK Bitonic::bitonic_sub(PTP_CALLBACK_INSTANCE Instance, PVOID Param, PTP_WORK Work)
{
	UNREFERENCED_PARAMETER(Instance);
	UNREFERENCED_PARAMETER(Work);

	ThreadParam* pThreadParam = (ThreadParam*)Param;
	Bignum start	= pThreadParam->start;
	Bignum end		= pThreadParam->end;
	Bignum block = pThreadParam->block;
	Bignum step = pThreadParam->step;
	std::vector<Bignum>* pElement = pThreadParam->pElement;

	for (Bignum idx = start; idx <= end; idx++)
	{
		Bignum e = idx ^ step;
		if (e > idx)
		{
			Bignum v1 = (*pElement)[idx];
			Bignum v2 = (*pElement)[e];
			if ((idx & block) != 0)
			{
				if (v1 < v2)
				{
					(*pElement)[e] = v1;
					(*pElement)[idx] = v2;
				}
			}
			else {
				if (v1 > v2)
				{
					(*pElement)[e] = v1;
					(*pElement)[idx] = v2;
				}
			}
		}
	}
}