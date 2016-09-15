#pragma once
#include <ctime>
#include <cstdlib>

class Random {
private:
	double start;
	double end;
public:
	Random(double start,double end)
	{
		srand(unsigned(time(0)));
		this->end = end;
		this->start = start;
	}
	double getRandom()
	{
		return start + (end - start)*rand() / (RAND_MAX);
	}
	void resetRange(double start, double end)
	{
		this->end = end;
		this->start = start;
	}
};
