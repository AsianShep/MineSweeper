#pragma once
#include <random>
class Random
{
private:
	static std::mt19937_64 random;

public:
	static int Int(int min, int max);

};

