#include "stdafx.h"
#include "bitonic.h"
#include <thread>

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

	Bignum range = new_size / threadNum;

	std::vector<std::thread> threads(threadNum);

	for (Bignum block = 1; block <= new_size; block <<= 1)
	{
		for (Bignum step = (block >> 1); step >= 1; step >>= 1)
		{
			for (int i = 0; i < threadNum; ++i)
			{
				Bignum start = range * i;
				Bignum end = min(new_size, range * (i + 1) - 1);
				threads[i] = std::thread(
					[this, start, end, block, step]() { Bitonic::bitonic_sub(elements, start, end, block, step); });
			}

			for (int i = 0; i < threadNum; ++i)
			{
				threads[i].join();
			}
		}
	}

	while (new_size > prev_size)
	{
		elements.pop_back();
		--new_size;
	}
}

void Bitonic::bitonic_sub(std::vector<Bignum> &vec, Bignum start, Bignum end, Bignum block, Bignum step)
{
	for (Bignum idx = start; idx <= end; ++idx)
	{
		Bignum e = idx ^ step;
		if (e > idx)
		{
			Bignum v1 = vec[idx];
			Bignum v2 = vec[e];
			if ((idx & block) != 0)
			{
				if (v1 < v2)
				{
					vec[e] = v1;
					vec[idx] = v2;
				}
			}
			else {
				if (v1 > v2)
				{
					vec[e] = v1;
					vec[idx] = v2;
				}
			}
		}
	}
}