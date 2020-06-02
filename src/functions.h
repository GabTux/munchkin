#pragma once

#include <random>

/**
 * Function widely used in one place.
 */

/**
 * Generate random int in <a, b>.
 * @param a Lower bound.
 * @param b Upper bound.
 * @return Random int.
 */
int randomInt(int a, int b);

void checkSum(std::string& inStr, std::size_t& checkHash);

void encryptDecrypt(std::string& inOutStr);