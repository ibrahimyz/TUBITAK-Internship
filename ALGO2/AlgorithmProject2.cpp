#include "include/util/periodGenerator.h"
#include "include\util\findIntervals.h"


int main()
{
	/*
	util1::BusSimulator bus_sim;

	
	util::StaticVector<int, util1::MAX_BUSES> intervals;

	int bus_number{ 0 };

	std::cin >> bus_number;

	for (int i = 0; i < bus_number; ++i)
		std::cin >> intervals[i];

	for (int i = 0; i < bus_number; ++i)
		bus_sim.addBus(intervals[i]);

	bus_sim.createSchedule();
	
	*/
	util2::FindIntervals f;

	util::StaticVector<int, util1::MAX_BUSES> newIntervals;

	f.setData();

	f.FindInterval(newIntervals);

	std::cout << " \nBus Periods: " << std::endl;


	f.printBuses(newIntervals);

	std::cout << "Bus Number: " << newIntervals.getSize() << std::endl;
	
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
