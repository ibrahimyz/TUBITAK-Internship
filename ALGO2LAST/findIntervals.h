#ifndef INCLUDE_UTIL_FINDINTERVALS_H_
#define INCLUDE_UTIL_FINDINTERVALS_H_

#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Split.h"

namespace util2 {

	const int MAX_BUS_NUM = 20; // Bus stop capacity

	class FindIntervals {

		// 2D Vector for input file
		util::StaticVector<util::StaticVector<int, 3>, 400> allTokens;

	public:

		// Split data in output file of periodCreator.h 
		void setData() {

			// Open file
			std::ifstream file("new2.txt");
			if (!file) {
				std::cerr << "Unable to open file!";
				return;
			}

			std::string line;

			// Split each line of file
			while (std::getline(file, line)) {
				auto tokens = algorithm::split<3>(line, ": -"); // Splitting by delimiters.
				if (tokens.getSize())
					allTokens.push_back(tokens); // Setting data to vector.
			}
			
			// Close file
			file.close();
			
			//Printing vector. It's not necessary!
			
			for (std::size_t i = 0; i < allTokens.getSize(); ++i) {
				for (std::size_t j = 0; j < allTokens[i].getSize(); ++j) {
					std::cout << allTokens[i][j] << " ";
				}
				std::cout << std::endl;
			}
			
		}

		// Get the required data in Vector(allTokens)
		int getData(int rowIndex, int colIndex) const{
			return allTokens[rowIndex][colIndex];		
		}

		// Convert hours to minutes
		int totalMinutes(int hours, int minutes) {
			return (hours - 6) * 60 + minutes;
		}

		// Count the buses have a same period at current time (mod = 0)
		int countBuses(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses, int time) {
			int checkCount{ 0 };
			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					if (time % buses[i][j] == 0)
					checkCount++;
				}				
			}
			return checkCount;
		}

		// Check the buses have a same period at current time (mod = 0)
		bool checkPeriod(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses, int time) {
			if (buses.getSize() == 0) // <= 1 olmasý daha doðru olabilir???!! alttaki size - 1 onu saðlýyor mu yoksa?
				return false;

			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					if (time % buses[i][j] == 0) {
						buses[i].push_back(0);
						return true;
					}
				}	
			}
			return false;
		}

		int checkDifferentPeriod(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses, int time) {
			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					if (time % buses[i][j] == 0)
					return buses[i][j];
				}
				
			}
		}


		void editIntervals(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses, int time) {
			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					if (time % buses[i][j] == 0) 
						buses[i].push_back(-1);
				}
			}
		}

		void secondInterval(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses, int arr[], int diffPeriod, int time) {
			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					if (buses[i][j] == -1) {
							buses[i].pop_back();
							buses[i].push_back(time - arr[diffPeriod]);
					}
				}
			}
		}


		// Print the intervals (periods) of buses
		void printBuses(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& buses) {
			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				for (std::size_t j = 0; j < buses[i].getSize(); ++j) {
					std::cout << buses[i][j];
				}
				std::cout << "\n";
			}
		}

		// Find bus intervals from vector.
		void FindInterval(util::StaticVector<util::StaticVector<int, 3>, MAX_BUS_NUM>& allIntervals) {

			// total bus number == size of intervals (vector)
			int diffPeriodCount = 0;
			int diffPeriodArr[100]{ 0 };
			int maybeIsNewBus[2]{ 0 }; // {time, true/false}
			int isDelayedBus[2]{ 0 };  // {time, true/false}

			for (std::size_t i = 0; i < allTokens.getSize(); ++i) {

				util::StaticVector<int, 3> intervals;
				int current_time = totalMinutes(getData(i, 0), getData(i, 1));
				int stop_count = getData(i, 2);
				int check_count = countBuses(allIntervals, current_time);

				if (check_count - 1 == stop_count) {

					isDelayedBus[

					// yani periodu deðiþen bir bus var!
					diffPeriodArr[diffPeriodCount++] = current_time; // 15->30 olunca bus yok yani 15'in periodu deðiþiyor
					editIntervals(allIntervals, current_time);
				}

				if (check_count + 1 == stop_count) {
					// 40 - 1 olunca, 30 olmasý gereken burada imiþ. Tabii 55 - 1 de saðlanýyorsa...
					secondInterval(allIntervals, diffPeriodArr, diffPeriodCount, current_time);

				}

				if (stop_count == 1) {
					intervals.push_back(current_time);
					allIntervals.push_back(intervals);

					// if this bus has a same period of any other buses, remove this bus.
					if (checkPeriod(allIntervals, current_time))
						allIntervals.pop_back();
				}

				else if (stop_count > 1) {
					// Check old buses and add 1. If this number equal to stop_count, there is a new bus.
					if (check_count + 1 == stop_count)
						intervals.push_back(current_time);
				}
			}

			/*/for (int i = 0; i < diffPeriodCount; ++i) {
				std::cout << bus_interval[i] << std::endl;
			}*/
		}
	};
}		// end namespace

#endif // !INCLUDE_UTIL_FINDINTERVALS_H_

