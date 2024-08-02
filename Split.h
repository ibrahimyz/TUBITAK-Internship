#ifndef INCLUDE_UTIL_SPLIT_H_
#define INCLUDE_UTIL_SPLIT_H_


#include<iostream>
#include<string>
#include "Vector.h"

namespace algorithm {

	template<std::size_t Capacity>
	util::StaticVector<int, Capacity> split(const std::string& str, const std::string& delimiters) {

		util::StaticVector<int, Capacity> tokens;
		size_t start = 0;
		size_t end = str.find_first_of(delimiters);

		while (end != std::string::npos) {
			std::string token = str.substr(start, end - start);
			if (!token.empty()) {
				int value = std::stoi(token);
				tokens.push_back(value);
			}

			start = end + 1;
			end = str.find_first_of(delimiters, start); // If no matches are found, the function returns string::npos. (std::string::find_first_of)
		}

		std::string token = str.substr(start);
		if (!token.empty()) {
			int value = std::stoi(token);
			tokens.push_back(value);
		}

		return tokens;
	}

}// end of namespace

/*
11:45 - 3 ilk ba�ta end = : oluyor. "11" ilk tokenimiz pushlan�yor.
start = end + 1 oluyor. End = yeni start'tan sonraki ilk delimeter yani - oluyor.
hala while i�indeyiz ve token "45" oluyor pushlan�yor. 
Start = end + 1 oluyor, end = art�k start'tan sonra delimeter olmad��� i�in npos oluyor.
While bitiyor. Start son de�eri ile tokeni olu�turuyor yani "3", pushlan�yor.
Return tokens ile allTokens vector'�ne token'lerimiz (row) pushlan�yor. [findIntervals.h]
*/

#endif // !INCLUDE_UTIL_SPLIT_H_