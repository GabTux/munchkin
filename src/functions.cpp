#include "functions.h"

int randomInt(int a, int b)
{
	// prepare seed for random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomIntGen(a, b);
	return randomIntGen(gen);
}