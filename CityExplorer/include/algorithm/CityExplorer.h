#ifndef INCLUDE_ALGORITHM_CITYEXPLORER_H_
#define INCLUDE_ALGORITHM_CITYEXPLORER_H_

#include<iostream>
#include<fstream>

#include "Algorithms.h"
#include "../headers/Vector.h"
#include "../headers/ObjectPool.h"


namespace algorithm {

	// The CSV file containing city data and others informations
	const char* path = "C:/Users/cpulo/source/repos/CityExplorer/CityExplorer/src/ilmesafe.csv";
	const std::size_t numOfCities = 81;
	const std::size_t maxEdgesPerCity = numOfCities - 1; // Maximum possible edges per city
	int maxLengths[numOfCities] = {};

	typedef util::StaticVector<std::size_t, numOfCities> Vector;

	// 1. Define the Graph Structure:
	class Graph {
	private:

		struct Edge {
			int weight; // Distance between cities
			std::size_t destination; // Index of the destination city
		};

		util::ObjectPool<Edge, numOfCities* numOfCities> edgePool; // Object pool for edges
		util::StaticVector<Edge, maxEdgesPerCity> adjList[numOfCities]; // Adjacency list for the graph

		// Initializes the graph
		void initializeGraph() {
			std::ifstream file(path);
			if (!file.is_open()) {
				std::cerr << "Failed to open file" << std::endl;
				return;
			}

			std::string line;
			std::size_t lineIndex = 0;

			// Read each line from the CSV file
			while (std::getline(file, line)) {
				for (std::size_t j = 0; j < numOfCities; ++j) {

					if (lineIndex != j) { // Skip self-connection
						Edge* E = nullptr; 
						int allocStatus = edgePool.Allocate(E); // Allocate an edge from the pool

						if (allocStatus == util::ErrorCode::NO_ERROR) {
							int weight1 = algorithm::findWeight<numOfCities>(line, j); // Find the weight for the edge
							E->weight = (weight1 >= 150 && weight1 <= 250) ? weight1 : -1;
							E->destination = j;
							adjList[lineIndex].push_back(*E); // Add edge to the adjacency list
						}
					}
				}
				++lineIndex; // Move to the next city
			}
			file.close(); // Close the file after reading
		}
		// Explores all paths from the given vertex using DFS
		void DFSWithLength(std::size_t vertex, bool visited[], int pathLength[], int& maxLength, Vector& longestPath,Vector& currentPath) {
			
			visited[vertex] = true; // Mark the current vertex as visited
			currentPath.push_back(vertex);	// Add the current vertex to the current path
			pathLength[vertex] = currentPath.getSize();	// Store the length of the current path for the vertex


			// Loop through all adjacent vertices (edges) of the current vertex
			for (std::size_t i = 0; i < adjList[vertex].getSize(); ++i) {
				const Edge& edge = adjList[vertex][i];

				// If the destination vertex is not visited and the edge has a valid weight, continue DFS
				if (!visited[edge.destination] && edge.weight != -1)
					DFSWithLength(edge.destination, visited, pathLength, maxLength, longestPath, currentPath);
			}

			// If the path from this vertex is longer than the previous max length, update the max length
			if (pathLength[vertex] > maxLength) {
				maxLength = pathLength[vertex];
				longestPath.clear();

				// Save the current path as the longest path
				for (std::size_t i = 0; i < currentPath.getSize(); ++i)
					longestPath.push_back(currentPath[i]);
			}

			// Backtrack by removing the last vertex from the current path (DFS)
			currentPath.pop_back();
		}

	public:
		// Constructor
		Graph() { initializeGraph(); }

		// Destructor
		~Graph() {
			for (std::size_t i = 0; i < numOfCities; ++i) {
				adjList[i].clear(); // Clear the adjacency list for each city
			}		
		} 

		// Performs a Depth-First Search (DFS) from the given source city (src)
		void DFSFromSource(std::size_t src) {
			bool visited[numOfCities] = { false };
			int pathLength[numOfCities] = {};
			int maxLength = 0;
			Vector longestPath;
			Vector currentPath;

			DFSWithLength(src, visited, pathLength, maxLength, longestPath, currentPath);

			maxLengths[src] = maxLength;
		}

		// Method to find and print the maximum value in the maxLengths array
		void findMaxLength() {
			int maxLength = 0;
			std::size_t maxIndex = 0;

			for (std::size_t i = 0; i < numOfCities; ++i) {
				if (maxLengths[i] > maxLength) {
					maxLength = maxLengths[i];
					maxIndex = i;
				}
			}
			std::cout << "The maximum path length is " << maxLength << " found at city " << maxIndex + 1 << ".\n";
		}

		// Print Graph
		void printGraph() {
			for (std::size_t i = 0; i < numOfCities; ++i) {
				std::cout << "City " << i << " connections:\n";

				for (auto& edge : adjList[i]) {
					if (edge.weight != -1) // Only print edges with valid weight
						std::cout << " -> City " << edge.destination << ", Weight: " << edge.weight << "\n";
				}
				std::cout << "\n";
			}
		}
	};
} // namespace algorithm

#endif // !INCLUDE_ALGORITHM_CITYEXPLORER_H_
