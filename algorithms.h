#ifndef INCLUDE_ALGORITHM_ALGORITHMS_H_
#define INCLUDE_ALGORITHM_ALGORITHMS_H_

#include <string>
#include <iostream>
#include <limits>
#include <stack>

#include "../util/Vector.h"

namespace algorithm {

	template<std::size_t Capacity>
	util::StaticVector<std::string, Capacity> split(const std::string& str, char delimiter) {

		util::StaticVector<std::string, Capacity> tokens;
		size_t start = 0;
		size_t end = str.find(delimiter);

		while (end != std::string::npos) {
			std::string token = str.substr(start, end - start);
			if (!token.empty())
				tokens.push_back(token);

			start = end + 1;
			end = str.find(delimiter, start);
		}
		tokens.push_back(str.substr(start));

		return tokens;
	}

	template<std::size_t Capacity>
	int findWeight(const std::string& line, std::size_t colIndex) {
		
		auto row = split<Capacity>(line, ',');
	
		return std::stoi(row[colIndex]);
	}


}

#endif // !INCLUDE_ALGORITHM_ALGORITHMS_H_
