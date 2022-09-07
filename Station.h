/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: July 21st, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {

	class Station {
		int m_id;
		std::string m_name;
		std::string m_desc;
		unsigned int m_serialNo;
		unsigned int m_numInStock;
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif