/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: July 21st, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#include "Station.h"
#include "Utilities.h"
#include <iomanip>
using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string& str) {
		Utilities util;
		bool more = true;
		size_t pos = 0u;
		m_id = ++id_generator;
		m_name = util.extractToken(str, pos, more);
		m_serialNo = stoi(util.extractToken(str, pos, more));
		m_numInStock = stoi(util.extractToken(str, pos, more));
		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
		m_desc = util.extractToken(str, pos, more);
	}
	const std::string& Station::getItemName() const {
		return m_name;
	}
	size_t Station::getNextSerialNumber() { 
		m_serialNo++;
		return (m_serialNo-1);
	}
	size_t Station::getQuantity() const {
		return m_numInStock;
	}
	void Station::updateQuantity() {
		if (m_numInStock > 0) {
			m_numInStock--;
		}
	}
	void Station::display(std::ostream& os, bool full) const {
		os << right << setfill('0') << setw(3) << m_id << " | " << setfill(' ') << left << setw(m_widthField) << m_name << "  | " << right << setfill('0') << setw(6) << m_serialNo << " | ";
		if (full) {
			os << setfill(' ') << setw(4) << m_numInStock << " | " << m_desc;
		}
		os << endl;
	}
}