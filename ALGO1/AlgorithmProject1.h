#ifndef INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_
#define INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_

#include<iostream>
#include<fstream>

#include "algorithms.h"
#include "../util/Vector.h"
#include "../util/ObjectPool.h"

namespace algorithm {

	const char* path = "C:\\Users\\ibrahim.yildiz\\Desktop\\ilmesafe (2).csv";
	const std::size_t numOfCities = 81;
	const std::size_t maxEdgesPerCity = numOfCities - 1; // Maximum possible edges per city
	int maxLengths[numOfCities] = {};


	// 1. Define the Graph Structure:
	class Graph {
	private:

		struct Edge {
			int weight;
			std::size_t destination;
		};

		util::ObjectPool<Edge, numOfCities* numOfCities> edgePool;
		util::StaticVector<Edge, maxEdgesPerCity> adjList[numOfCities];

		void initializeGraph() {
			std::ifstream file(path);
			if (!file.is_open()) {
				std::cerr << "Failed to open file" << std::endl;
				return;
			}

			std::string line;
			std::size_t lineIndex = 0;

			while (std::getline(file, line)) {
				for (std::size_t j = 0; j < numOfCities; ++j) {

					if (lineIndex != j) {
						Edge* E = nullptr;
						int allocStatus = edgePool.Allocate(E);

						if (allocStatus == util::ErrorCode::NO_ERROR) {
							int weight1 = algorithm::findWeight<numOfCities>(line, j);
							E->weight = (weight1 >= 150 && weight1 <= 250) ? weight1 : -1;
							E->destination = j;
							adjList[lineIndex].push_back(*E);
						}
					}
				}
				++lineIndex;
			}
			file.close();
		}

		void DFSWithLength(std::size_t vertex, bool visited[], int pathLength[], int& maxLength, util::StaticVector<std::size_t, numOfCities>& longestPath, util::StaticVector<std::size_t, numOfCities>& currentPath) {
			visited[vertex] = true;
			currentPath.push_back(vertex);
			pathLength[vertex] = currentPath.getSize();

			for (std::size_t i = 0; i < adjList[vertex].getSize(); ++i) {
				const Edge& edge = adjList[vertex][i];
				if (!visited[edge.destination] && edge.weight != -1)
					DFSWithLength(edge.destination, visited, pathLength, maxLength, longestPath, currentPath);
			}

			if (pathLength[vertex] > maxLength) {
				maxLength = pathLength[vertex];
				longestPath.clear();
				for (std::size_t i = 0; i < currentPath.getSize(); ++i)
					longestPath.push_back(currentPath[i]);
			}

			currentPath.pop_back();

		}

	public:
		Graph() { initializeGraph(); }

		~Graph() {} // clear adjList[] 

		void DFSFromSource(std::size_t src) {
			bool visited[numOfCities] = { false };
			int pathLength[numOfCities] = {};
			int maxLength = 0;
			util::StaticVector<std::size_t, numOfCities> longestPath;
			util::StaticVector<std::size_t, numOfCities> currentPath;

			DFSWithLength(src, visited, pathLength, maxLength, longestPath, currentPath);

			maxLengths[src] = maxLength;

			/*std::cout << "Longest Destinations from Source " << src << " with length " << maxLength + 1 << ":\n";
			for (std::size_t i = 0; i < longestPath.getSize(); ++i) {
				std::cout << longestPath[i]+1;
				if (i != longestPath.getSize() - 1) {
					std::cout << "-> ";
				}
			}
			std::cout << std::endl;*/
		}

		// Method to find and print the maximum value in the maxLengths array
		void findMaxLength() const {
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
					if (edge.weight != -1)
						std::cout << " -> City " << edge.destination << ", Weight: " << edge.weight << "\n";
				}
				std::cout << "\n";
			}
		}
		/*
			for (std::size_t i = 0; i < numOfCities; ++i) {
				if (visited[i]) {
					std::cout << "Node: " << i << ", Length: " << pathLength[i] << std::endl;
				}
			}
			// Print the path lengths
			std::cout << "------\n";
			std::cout <<" max: " <<  * std::max_element(pathLength, pathLength + 81) << std::endl;
			std::cout << "------\n";
			*/


		/* DFS based!
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
		
		int DFS(std::size_t vertex, util::StaticVector<bool, numOfCities>& visited, util::StaticVector<std::size_t, numOfCities>& counterPerNode, std::stack<std::size_t>& DFSStack) {
			int oldCounter = 0;
			int tempCounter = 0;
			int newCounter = 0;

			DFSStack.push(vertex);
			while (!DFSStack.empty()) {
				std::size_t u = DFSStack.top();
				DFSStack.pop();
				newCounter++;

				if (!visited[u]) {
					visited[u] = true;

					//counterPerNode[u] = newCounter;

					tempCounter = oldCounter;
					if (oldCounter < newCounter) oldCounter = newCounter;

					for (auto& edge : adjList[u]) {
						if (!visited[edge.destination] && edge.weight != -1) {
							edge.myCounter++;
							DFSStack.push(edge.destination);
						}
						else 
							newCounter = tempCounter;
					}
				}
			}
			return oldCounter-1;
		}


		void myLongestPath(std::size_t src) {
			std::stack<std::size_t> Stack;
			util::StaticVector<bool, numOfCities> visited;
			util::StaticVector<std::size_t, numOfCities> pathCount; // Initialize path count for each city
			util::StaticVector<std::size_t, numOfCities> allNodeCount;
			util::StaticVector<std::size_t, numOfCities>counterPerNode;

			for (std::size_t i = 0; i < numOfCities; ++i) {
				visited[i] = false;
				counterPerNode[i] = 0;
				pathCount[i] = 0;
				allNodeCount[i] = 0;
			}

			std::cout << DFS(src, visited, counterPerNode, Stack) << std::endl;
			
			for (std::size_t i = 0; i < numOfCities; ++i)
				std::cout << counterPerNode[i] << std::endl;

		}*/

		/*
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
			}
		}*/
		
	};
} // namespace algorithm

#endif // !INCLUDE_ALGORITHM_ALGORITHMPROJECT1_H_
