#ifndef INCLUDE_ALGORITHMS_FINDINTERVALS_H_
#define INCLUDE_ALGORITHMS_FINDINTERVALS_H_

#include <iostream>
#include <fstream>
#include "../util/Vector.h"
#include "../util/Split.h"

namespace util4 {

	const int MAX_BUS_NUM = 20; // Bus stop capacity

	class FindIntervals {

		// 2D Vector for input file
		util::StaticVector<util::StaticVector<int, 3>, 400> allTokens;

	public:

		// Split data in output file of periodCreator.h 
		void setData() {

			// Open file
			std::ifstream file("C:\\Users\\cpulo\\source\\repos\\BusScheduling\\BusScheduling\\src\\output4.txt");
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

		// Count and check the buses have a same period with delays(deviations) at current time [mod = 0]
		int checkBuses(util::StaticVector<int, MAX_BUS_NUM>& buses, int time, int& checkCount) {
			bool checkPeriod = false;

			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {

				int deviation = buses[i] * 10 / 100;

				for (int j = -deviation; j <= deviation; ++j) {
					if ((time + j) % buses[i] == 0) {
						checkCount++;
						checkPeriod = true;
					}						
				}
			}
			return checkPeriod;
		}

		// Print the intervals (periods) of buses
		void printBuses(util::StaticVector<int, MAX_BUS_NUM>& buses) {
			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				std::cout << buses[i] << std::endl;
			}
			std::cout << "\n";
		}

		// TO DO 1: 10 VE 19'LUK 2 OTOBÜS VAR AMA 19, 10'UN 1DK ERKEN GELMÝÞÝ OLUYOR...			xxx
		// TO DO 2: TAM SAPMA ZAMANI OLAN BAÞKA BÝR OTOBÜS VARSA SIKINTI, BUSCOUNT > 2 ?..		xxx
		// FARKLI SAPMALI OTOBÜSLERLE DE DENE...												xxx

		// Find bus intervals from vector.
		void FindInterval(util::StaticVector<int, MAX_BUS_NUM>& intervals) {

			// total bus number == size of intervals (vector)

			for (std::size_t i = 0; i < allTokens.getSize(); ++i) {

				int current_time = totalMinutes(getData(i, 0), getData(i, 1));
				int stop_count = getData(i, 2);
				int checkCount{ 0 };

				if (stop_count == 1) {
					
					intervals.push_back(current_time);

					// if this bus has a same period with deviation of any other buses, remove this bus.
					if (checkBuses(intervals, current_time, checkCount))
						intervals.pop_back();
				}

				else if (stop_count > 1) {
					bool checkPeriod = checkBuses(intervals, current_time, checkCount);

					// Check old buses and add 1. If this number equal to stop_count, there is a new bus.
					if (checkCount + 1 == stop_count)
						intervals.push_back(current_time);

				}
			}
		}
	};
}		// end namespace

#endif // !INCLUDE_UTIL_FINDINTERVALS2_H_

/*

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
		bool checkPeriod(util::StaticVector<int, MAX_BUS_NUM>& buses, int time) {

			for (std::size_t i = 0; i < buses.getSize() - 1; ++i) {
				if (time % buses[i] == 0)
					return true;
			}

			return false;
		}

		// check deviation ve period ayný þeyleri yapýyor aslýnda. Deviation geliþmiþ versiyonu.

*/



/*
for (std::size_t i = 0; i < buses.getSize(); ++i) {

				int deviation = buses[i] * 10 / 100;
				int negDeviation = -1 * deviation;
				//util::StaticVector<int, 20> busDeviations;

				for (std::size_t j = negDeviation; j <= deviation; ++j) {
					if ((time + j) % buses[i] == 0)
						return true;
					//busDeviations.push_back(j);
				}

				//allDeviations.push_back(busDeviations);
			}
*/

/*
			util::StaticVector < util::StaticVector<int, 20>, MAX_BUS_NUM> allDeviations;

			for (std::size_t i = 0; i < buses.getSize(); ++i) {

				int deviation = buses[i] * 10 / 100;
				int negDeviation = -1 * deviation;
				util::StaticVector<int, 20> busDeviations;

				for (std::size_t j = negDeviation; j <= deviation; ++j) {
					busDeviations.push_back(j);
				}

				allDeviations.push_back(busDeviations);
			}

			// 1 bus varsa, 1 busDeviations var zaten. O yüzden 2 for loop yetiyor.

			for (std::size_t i = 0; i < buses.getSize(); ++i) {
				for (std::size_t j = 0; j < allDeviations[i].getSize(); ++j) {
					if ((time + allDeviations[i][j]) % buses[i] == 0)
						return true;
				}
			}
*/

/*
		// eðer 06.09 geçe olan 2 bus ve 6 geçe olan 1 bus varsa aslýnda 3 geçe olan bus vardýr!
	int checkTraffic(util::StaticVector<int, MAX_BUS_NUM>&buses, int modCount[]) {

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
		}
*/