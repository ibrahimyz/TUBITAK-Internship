#include <fstream>
#include <string>
#include <iostream>

#include "include/util/Vector.h"
#include "include/algorithm/AlgorithmProject1.h"

algorithm::Graph G1;

int main() {

	/*
	for (size_t src = 0; src < 81; ++src) {
		std::cout << "City " << src << " max: ";

		int max = G1.longestPath(src);

		std::cout << max << std::endl;
	}*/
	
	//G1.longestPath(77);


	//G1.printGraph();

	for (size_t src = 0; src < 81; ++src) {
		//std::cout << src+1 << ": \n";
		G1.DFSFromSource(src);
		//std::cout << "\n";
	}
		
	G1.findMaxLength();

	return 0;
}
