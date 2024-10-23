#include <iostream>

#include "../include/headers/Vector.h"
#include "../include/algorithm/CityExplorer.h"

// Create an instance of the Graph class
algorithm::Graph G1;

int main() {

	// Perform Depth-First Search (DFS) from each city
	for (size_t src = 0; src < 81; ++src) {
		G1.DFSFromSource(src); // Explore all paths starting from the current city
	}
	// Find and print the maximum path length among all cities
	G1.findMaxLength();

	return 0;
}

