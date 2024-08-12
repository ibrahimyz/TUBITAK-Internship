//#include "include/util/periodGenerator.h" //util1
//#include "include\util\findIntervals.h"		//util2
#include "include/util/periodGenerator2.h"	//util3
#include "include\util\findIntervals2.h"		//util4



int main() {
	/*
	util1::BusSimulator bus_sim;
	int bus_count;

	std::cout << "Enter the number of buses: ";
	std::cin >> bus_count;

	for (int i = 0; i < bus_count; ++i) {
		std::cout << "Enter the number of intervals for bus " << (i + 1) << ": ";
		int interval_count;
		std::cin >> interval_count;

		util::StaticVector<int,2> intervals;
		int num;
		std::cout << "Enter the intervals: ";
		for (int j = 0; j < interval_count; ++j) {
			std::cin >> num;
			intervals.push_back(num);
		}

		bus_sim.addBus(intervals);
	}												// 10 15 20 25 (10 20)

	bus_sim.createSchedule();
	*/
	

	//------------------------------------------------------
	//TEKLİ INTERVALLERİ BULAN MAIN
/*
	util3::BusSimulator bus_sim;

	util::StaticVector<int, util3::MAX_BUSES> intervals;

	int bus_number{ 0 };

	std::cin >> bus_number;

	for (int i = 0; i < bus_number; ++i)
		std::cin >> intervals[i];

	for (int i = 0; i < bus_number; ++i)
		bus_sim.addBus(intervals[i]);

	bus_sim.createSchedule();
	*/
	
	util4::FindIntervals f;

	util::StaticVector<int, util3::MAX_BUSES> intervals;

	f.setData();

	f.FindInterval(intervals);

	std::cout << "\nBus Periods(Intervals): " << std::endl;
	f.printBuses(intervals);

	std::cout << "Bus Number: " << intervals.getSize() << std::endl;
	

	/*
	 // -------------------------
	util2::FindIntervals f;

	util::StaticVector<util::StaticVector<int, 3>, util1::MAX_BUSES> newIntervals;

	f.setData();

	f.FindInterval(newIntervals);

	std::cout << "\nBus Periods(Intervals): " << std::endl;
	f.printBuses(newIntervals);

	std::cout << "Bus Number: " << newIntervals.getSize() << std::endl;
*/
	return 0;
}
/*
5 
15
25
10
45
60
30		5 - 8 - 9 - 12 - 13 - 16 - 24 - 31 -
75
--
7 bus number
3
7
9
4
60 ///	06.21 ve 06.27 silindi
20
35
*/
