#ifndef INCLUDE_UTIL_FINDINTERVALS2_H_
#define INCLUDE_UTIL_FINDINTERVALS2_H_

#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Split.h"

namespace util4 {

	const int MAX_BUS_NUM = 20; // Bus stop capacity

	class FindIntervals {

		// 2D Vector for input file
		util::StaticVector<util::StaticVector<int, 3>, 400> allTokens;

	public:

		// Split data in output file of periodCreator.h 
		void setData() {

			// Open file
			std::ifstream file("output5.txt");
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
		int getData(int rowIndex, int colIndex) const {
			return allTokens[rowIndex][colIndex];
		}

		// Convert hours to minutes
		int totalMinutes(int hours, int minutes) {
			return (hours - 6) * 60 + minutes;
		}

		// Count the buses have a same period at current time (mod = 0)
		int countBuses(util::StaticVector<int, MAX_BUS_NUM>& buses, int time) {
			int checkCount{ 0 };
			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				if (time % buses[i] == 0)
					checkCount++;
			}
			return checkCount;
		}

		// Check the buses have a same period at current time (mod = 0)
		int checkPeriod(util::StaticVector<int, MAX_BUS_NUM>& buses, int time) {
			if (buses.getSize() == 0) // <= 1 olmasý daha doðru olabilir???!!
				return false;

			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				if (time % buses[i] == 0)
					return true;
			}

			return false;
		}

		// Print the intervals (periods) of buses
		void printBuses(util::StaticVector<int, MAX_BUS_NUM>& buses) {
			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				std::cout << buses[i] << std::endl;
			}
			std::cout << "\n";
		}

		/*// eðer 06.09 geçe olan 2 bus ve 6 geçe olan 1 bus varsa aslýnda 3 geçe olan bus vardýr!
		int checkTraffic(util::StaticVector<int, MAX_BUS_NUM>& buses, int modCount[]) {

			static int count = 0;
			for (std::size_t i = buses.getSize() - 1; i > 0; --i) {
				int mod = buses[i] % buses[i - 1];
				modCount[count] = mod;
				count++;
			}

			int max = 0;
			for (std::size_t i = 0; i < count; ++i) {

				if (max < modCount[i])
					max = modCount[i];
			}

			return max;
		}*/

		// Find bus intervals from vector.
		void FindInterval(util::StaticVector<int, MAX_BUS_NUM>& intervals) {

			// total bus number == size of intervals (vector)

			for (std::size_t i = 0; i < allTokens.getSize(); ++i) {

				int current_time = totalMinutes(getData(i, 0), getData(i, 1));
				int stop_count = getData(i, 2);
				int checkCount{ 0 };

				if (stop_count == 1) {
					intervals.push_back(current_time);

					// if this bus has a same period of any other buses, remove this bus.
					if (checkPeriod(intervals, current_time))
						intervals.pop_back();
				}

				else if (stop_count > 1) {
					checkCount = countBuses(intervals, current_time);

					//std::cout << checkTraffic(intervals, modCount) << std::endl;

					// Check old buses and add 1. If this number equal to stop_count, there is a new bus.
					if (checkCount + 1 == stop_count)
						intervals.push_back(current_time);
				}
			}
		}
	};
}		// end namespace

#endif // !INCLUDE_UTIL_FINDINTERVALS2_H_

