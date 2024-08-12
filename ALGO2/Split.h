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
11:45 - 3 ilk baþta end = : oluyor. "11" ilk tokenimiz pushlanýyor.
start = end + 1 oluyor. End = yeni start'tan sonraki ilk delimeter yani - oluyor.
hala while içindeyiz ve token "45" oluyor pushlanýyor. 
Start = end + 1 oluyor, end = artýk start'tan sonra delimeter olmadýðý için npos oluyor.
While bitiyor. Start son deðeri ile tokeni oluþturuyor yani "3", pushlanýyor.
Return tokens ile allTokens vector'üne token'lerimiz (row) pushlanýyor. [findIntervals.h]
*/

#endif // !INCLUDE_UTIL_SPLIT_H_