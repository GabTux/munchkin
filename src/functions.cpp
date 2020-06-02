#include "functions.h"
#include "Exceptions.h"

int randomInt(int a, int b)
{
	// prepare seed for random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomIntGen(a, b);
	return randomIntGen(gen);
}

void checkSum(std::string &inStr, std::size_t& checkHash)
{
	if (inStr.empty())
		throw GameError("No size of check string.");

	checkHash = std::hash<std::string>{}(inStr);
}

void encryptDecrypt(std::string& inOutStr)
{
	if (inOutStr.empty())
		throw GameError("No size of encrypt string.");

	std::string key = "MunChKin";

	for (unsigned int i = 0; i < inOutStr.size(); i++)
	{
		if ((inOutStr[i] ^ key[i % key.size()]) == '\n')
			continue;
		inOutStr[i] ^= key[i % key.size()];
	}
}
