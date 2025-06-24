#ifndef INCLUDE_UTIL_PERIODCREATOR_H_
#define INCLUDE_UTIL_PERIODCREATOR_H_

/*
1 BUS
AMA
+2
FARKLI
PERİODU
OLABİLİR
*/

#include <iostream>
#include <fstream>
#include "Vector.h"

namespace util1 {

	// may be these variables take as input
	const int MAX_BUSES = 20; // Bus stop capacity
	const int start_time = 0; // start time (06.00) 
	const int end_time = 360; // end time (12.00)	
	const int time_interval = 1; // every single minute

	class Bus {
		util::StaticVector<int, 2> bus_intervals;
		int interval_index;
		int next_arrival;
		int bus_arrived;

	public:
		Bus() : interval_index(0), next_arrival(0), bus_arrived(0) {}

		Bus(const util::StaticVector<int, 2>& _bus_intervals) : bus_intervals(_bus_intervals), interval_index(0), 
															   next_arrival(_bus_intervals[0]), bus_arrived(0) {}

		// if the bus is at the stop at current time, check it.
		void checkArrival(int time) {
			if (time == next_arrival) {
				interval_index = (interval_index + 1) % bus_intervals.getSize(); // 0 -> 1, 1 -> 0
				next_arrival += bus_intervals[interval_index];
				bus_arrived++;
			}
		}

		// if the bus came arrive before, reset it to 0.
		void resetArrivals() {
			bus_arrived = 0;
		}

		// return the bus_arrived number
		int getArrived() const {
			return bus_arrived;
		}
	};

	class BusSimulator {
		util::StaticVector<Bus, MAX_BUSES> buses;

		// Convert total minutes to hours:minutes 
		void minutesToTime(int minutes, int& hours, int& mins) {
			hours = 6 + minutes / 60;
			mins = minutes % 60;
		}

	public:
		BusSimulator() {} // bus_count == buses.getSize()

		// Add bus to buses vector with Bus constructor
		void addBus(const util::StaticVector<int, 2>& _bus_intervals) {
				buses.push_back(Bus(_bus_intervals));
		}

		// Create the bus schedule
		void createSchedule() { 

			// Open file
			std::ofstream file("new3.txt");
			if (!file) {
				std::cerr << "Error opening file!" << std::endl;
				return;
			}

			// Create stop_count and hours:minutes
			for (int time = start_time; time <= end_time; time += time_interval) {

				int bus_count_at_stop = 0;

				for (int i = 0; i < buses.getSize(); ++i) {
					buses[i].checkArrival(time);
					bus_count_at_stop += buses[i].getArrived();
					buses[i].resetArrivals();
				}

				int hours, minutes;
				minutesToTime(time, hours, minutes);

				// Type to file
				file << (hours < 10 ? "0" : "") << hours << ":"
					<< (minutes < 10 ? "0" : "") << minutes << " - "
					<< bus_count_at_stop << std::endl;
			}

			// Close file
			file.close();
		}
	};
} // end namespace

#endif // !INCLUDE_UTIL_PERIODCREATOR_H_
