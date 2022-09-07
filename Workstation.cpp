/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: August 2nd, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#include "Workstation.h"
#include <iostream>
using namespace std;

namespace sdds {
	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;
	Workstation::Workstation(const std::string& src) : Station(src) {}
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder() {
		bool removed = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1) {
				if (m_pNextStation != nullptr) {
					*m_pNextStation += std::move(m_orders.front());
					m_orders.pop_front();
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
						removed = true;
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
						removed = true;
					}
					m_orders.pop_front();
				}
			}	
		}
		return removed;		
	}
	void Workstation::setNextStation(Workstation* station = nullptr) {
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const {
		if (m_pNextStation != nullptr) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		}
		else {
			os << getItemName() << " --> End of Line" << endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}