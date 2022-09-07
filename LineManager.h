/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: August 2nd, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include "Workstation.h"
#include <vector>


namespace sdds {
	class LineManager {
		static std::vector<Workstation*> m_activeLine;
		static size_t m_cntCustomerOrder;
		static Workstation* m_firstStation;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};

}

#endif