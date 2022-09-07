/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: August 2nd, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation;
	public:
		Workstation(const std::string& src);
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};


}

#endif