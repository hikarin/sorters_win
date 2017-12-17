#pragma once

#include <vector>
#include <string>

typedef size_t Bignum;

class Sort
{
public:
	Sort(std::vector<Bignum> v);
	virtual ~Sort();

	virtual void execute() = 0;

	bool check() const;
	static void init(std::vector<Bignum>& v);
protected:
	static void swap(Bignum& a, Bignum& b)
	{
		auto tmp = a;
		a = b;
		b = tmp;
	}

	std::vector<Bignum> elements;
};