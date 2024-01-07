#pragma once

#include <string>

namespace FNV {
	const unsigned int fnvPrime = 0x811C9DC5;

	static unsigned int Hash(const std::string str) {
		unsigned int hash = 0;
		unsigned int i = 0;
		size_t len = str.length();

		for (i = 0; i < len; i++)
		{
			hash *= fnvPrime;
			hash ^= (str[i]);
		}

		return hash;
	}
}