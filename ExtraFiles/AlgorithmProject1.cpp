#include <fstream>
#include <string>
#include <iostream>

#include "include/util/Vector.h"
#include "include/algorithm/AlgorithmProject1.h"

algorithm::Graph G1;

int main() {

	G1.initializeGraph();	
	for (size_t src = 0; src < 81; ++src) {
		std::cout << "City " << src << " max: ";

		int max = G1.longestPath(src);

		std::cout << max << std::endl;
	}
	
	//G1.longestPath(77);


	//G1.printGraph();
	return 0;
}
