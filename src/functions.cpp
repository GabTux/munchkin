#include "functions.h"
#include "Exceptions.h"
#include <zlib.h>

int randomInt(int a, int b)
{
	// prepare seed for random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomIntGen(a, b);
	return randomIntGen(gen);
}

void checkSum(std::string &inStr, unsigned long& checkHash)
{
	if (inStr.empty())
		throw GameError("No size of check string.");

	unsigned long crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (const unsigned char*)inStr.c_str(), inStr.size());

	checkHash = crc;
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
