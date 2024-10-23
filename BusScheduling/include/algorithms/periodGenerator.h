#ifndef INCLUDE_ALGORITHMS_PERIODGENERATOR_H_
#define INCLUDE_ALGORITHMS_PERIODGENERATOR_H_


/*
NORMAL
ÇALIÞAN
TEK TEK BUS'LARI
GENERATE
EDEN
KOD
*/


#include <iostream>
#include <fstream>
#include "../util/Vector.h"

namespace util3 {

	// may be these variables take as input
	const int MAX_BUSES = 20; // Bus stop capacity
	const int start_time = 0; // start time (06.00) 
	const int end_time = 360; // end time (12.00)	
	const int time_interval = 1; // every single minute

	class Bus {
		int bus_interval;
		int next_arrival;
		int bus_arrived;

	public:
		Bus() : bus_interval(0), next_arrival(0), bus_arrived(0) {}

		Bus(int _interval) : bus_interval(_interval), next_arrival(_interval), bus_arrived(0) {}

		// if the bus is at the stop at current time, check it.
		void checkArrival(int time) {
			if (time == next_arrival) {
				next_arrival += bus_interval;
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

		// Convert to total minutes to hours:minutes 
		void minutesToTime(int minutes, int& hours, int& mins) {
			hours = 6 + minutes / 60;
			mins = minutes % 60;
		}

	public:
		BusSimulator() {} // bus_count == buses.getSize()

		// Add bus to buses array with Bus constructor
		void addBus(int _interval) {
			buses.push_back(Bus(_interval));
		}

		// Create the bus schedule
		void createSchedule() {

			// Open file
			std::ofstream file("output5.txt");
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