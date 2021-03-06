// sorters_win.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "bubble.h"
#include "comb.h"
#include "quick.h"
#include "bitonic.h"
#include <iostream>
#include <chrono>

void MeasureSorting(Sort& sort, std::vector<Bignum> v, std::string name)
{
	auto start = std::chrono::system_clock::now();
	sort.execute();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << name << ": " << (sort.check() ? "OK " : "NG ") << diff.count() << "[s]\n";;
}


int main()
{
	for (Bignum array_size = 32; array_size < 50 * 1000 * 1000; array_size *= 2)
	{
		std::cout << "array_size: " << array_size << "\n";
		std::vector<Bignum> v(array_size);
		Sort::init(v);
		
		//	Bubble Sort
		{
			Bubble bubble(v);
			MeasureSorting(bubble, v, "Bubble");
		}

		//	Comb Sort
		{
			Comb comb(v);
			MeasureSorting(comb, v, "Comb");
		}

		//	Quick Sort
		{
			Quick quick(v);
			MeasureSorting(quick, v, "Quick");
		}

		//	Bitonic Sort
		{
			for (int i = 1; i <= 8; i *= 2)
			{
				Bitonic bitonic(v, i);
				MeasureSorting(bitonic, v, "Bitonic(threadNum:" + std::to_string(i) + ")");
			}
		}

		std::cout << "\n";
	}

	system("pause");

    return 0;
}