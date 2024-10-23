#ifndef INCLUDE_ALGORITHM_ALGORITHMS_H_
#define INCLUDE_ALGORITHM_ALGORITHMS_H_

#include <string>
#include <iostream>

#include "../headers/Vector.h"

namespace algorithm {

	// Splits a string into tokens based on a specified delimiter
	template<std::size_t Capacity>
	util::StaticVector<std::string, Capacity> split(const std::string& str, char delimiter) {

		util::StaticVector<std::string, Capacity> tokens; // Vector to store the resulting tokens
		size_t start = 0;
		size_t end = str.find(delimiter); // Find the position of the first delimiter

		// Loop until no more delimiters are found
		while (end != std::string::npos) {
			std::string token = str.substr(start, end - start); // Extract the token
			if (!token.empty())
				tokens.push_back(token); // Add the token to the vector

			start = end + 1;
			end = str.find(delimiter, start); // Find the next delimiter
		}
		tokens.push_back(str.substr(start)); // Add the last token after the last delimiter

		return tokens; // Return the vector of tokens
	}

	// // Finds the weight (distances between cities) 
	template<std::size_t Capacity>
	int findWeight(const std::string& line, std::size_t colIndex) {

		auto row = split<Capacity>(line, ','); // Split the line into tokens

		return std::stoi(row[colIndex]); // Convert the token at colIndex to an integer and return it
	}


}

#endif // !INCLUDE_ALGORITHM_ALGORITHMS_H_
