#ifndef INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_
#define INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_

#include<iostream>
#include<fstream>
#include<stack>
#include<limits>
#include<vector>
#include <algorithm> // for std::reverse


#include "algorithms.h"
#include "../util/Vector.h"
#include "../util/ObjectPool.h"

namespace algorithm {

	const char* path = "C:\\Users\\ibrahim.yildiz\\Desktop\\ilmesafe (2).csv";
	const std::size_t numOfCities = 81;
	const std::size_t maxEdgesPerCity = numOfCities - 1; // Maximum possible edges per city
	const int MIN_INT = std::numeric_limits<int>::min();

	// 1. Define the Graph Structure:
	class Graph {
	private:

		struct Edge {
			int weight;
			std::size_t destination;
		};

		util::ObjectPool<Edge, numOfCities* numOfCities> edgePool;
		util::StaticVector<Edge, maxEdgesPerCity> adjList[numOfCities];

		// DFS based!
		void TopologicalSortUtil(std::size_t v, util::StaticVector<bool, numOfCities>& visited, std::stack<std::size_t>& Stack) {

			visited[v] = true;

			//std::cout << "topological" << v << std::endl;

			for (auto& edge : adjList[v]) {
				if (!visited[edge.destination] && edge.weight != -1) {
					TopologicalSortUtil(edge.destination, visited, Stack);
				}
			}
			Stack.push(v);
		}

	public:
		Graph() { initializeGraph(); }

		~Graph() {} // clear adjList[] 

		void initializeGraph() {
			std::ifstream file(path);
			if (!file.is_open()) {
				std::cerr << "Failed to open file" << std::endl;
				return;
			}

			std::string line;
			std::size_t lineIndex = 0;

			while (std::getline(file, line) && lineIndex < numOfCities) {
				for (std::size_t j = 0; j < numOfCities; ++j) {

					if (lineIndex != j) {
						Edge* E = nullptr;
						int allocStatus = edgePool.Allocate(E);

						if (allocStatus == util::ErrorCode::NO_ERROR) {
							E->destination = j;
							int weight1 = algorithm::findWeight<numOfCities>(line, j);
							E->weight = (weight1 >= 150 && weight1 <= 250) ? weight1 : -1;
							adjList[lineIndex].push_back(*E);
						}
					}
				}
				++lineIndex;
			}
			file.close();
		}

		// The longest path algorithm
		int longestPath(std::size_t src) {
			std::stack<std::size_t> Stack;
			util::StaticVector<bool, numOfCities> visited;
			util::StaticVector<int, numOfCities> dist;
			util::StaticVector<std::size_t, numOfCities> pathCount; // Initialize path count for each city

			for (std::size_t i = 0; i < numOfCities; ++i) {
				dist[i] = MIN_INT;
				visited[i] = false;
				pathCount[i] = 0;
			}

			dist[src] = 0;

			for (std::size_t i = 0; i < numOfCities; ++i) {
				if (!visited[i])
					TopologicalSortUtil(i, visited, Stack);
			}

			while (!Stack.empty()) {

				std::size_t v = Stack.top();
				//std::cout << "current city: " << v << std::endl;
				Stack.pop();

				if (dist[v] != MIN_INT) {
					for (auto& edge : adjList[v]) {
						if (edge.destination != src && edge.weight != -1 && dist[edge.destination] < dist[v] + edge.weight) {
							dist[edge.destination] = dist[v] + edge.weight;
							pathCount[edge.destination] = pathCount[v] + 1;
						}
					}
				}
			}

			// Find maximum path count among all cities
			int maxPathCount = 0;
			for (std::size_t i = 0; i < numOfCities; ++i) {
				if (pathCount[i] > maxPathCount) {
					maxPathCount = pathCount[i];
				}
			}

			return maxPathCount;

			/*
			for (std::size_t i = 0; i < numOfCities; ++i) {
				if (i == src) continue;
				if (dist[i] == MIN_INT)
					std::cout << "City " << i + 1 << ": No path\n";
				else
					std::cout << "City " << i + 1 << ": " << dist[i] << " (Visited " << pathCount[i] << " cities) \n";
			}*/
		}

		// Print Graph
		void printGraph() {
			for (int i = 0; i < numOfCities; ++i) {
				std::cout << "City " << i+1 << " connections:\n";
				for (auto& edge : adjList[i]) {
					std::cout << " -> City " << edge.destination << ", Weight: " << edge.weight << "\n";
				}
				std::cout << "\n";
			}
		}
	};
} // namespace algorithm

#endif // !INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_
