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

/**
 * Create check hash for given string.
 * @param inStr Source string.
 * @param checkHash Where to save generated hash.
 */
void checkSum(std::string& inStr, std::size_t& checkHash);

/**
 * Simply do XOR with given string and defined key.
 * NOTE: It will skip "xoring", if the result will be newline.
 * @param inOutStr given string.
 */
void encryptDecrypt(std::string& inOutStr);