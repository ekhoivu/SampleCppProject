/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: August 2nd, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#include "LineManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include<numeric>

using namespace std;

namespace sdds {
	vector<Workstation*> LineManager::m_activeLine;
	size_t LineManager::m_cntCustomerOrder = 0;
	Workstation* LineManager::m_firstStation = nullptr;
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
		string temp, firstName, secondName;
		vector<string> firstStationNames{}, secondStationNames{}, difference{};
		m_cntCustomerOrder = g_pending.size();
		ifstream fo(file);
		if (!fo) {
			throw string("Unable to open this file");
		}
		while (!fo.eof()) {
			Utilities util;
			getline(fo, temp);
			if (temp != "") {
			bool more = true;
			size_t pos = 0u;
			try {
			firstName = util.extractToken(temp, pos, more);
			}
			catch (...) {
				throw string("There is an error with a first station name in the file!");
			}
			firstStationNames.push_back(firstName);
			if (more) {
				try {
					secondName = util.extractToken(temp, pos, more);
				}
				catch (...) {
					throw string("There is an error with a second station name in the file!");
				}
				secondStationNames.push_back(secondName);
			}
			else {
				secondName = "";
			}
			int indexFirst = 0, indexSecond = 0;
			auto existFirst = find_if(stations.begin(), stations.end(), [&](const Workstation* src) { return (src->getItemName() == firstName); });
			if (existFirst != stations.end()) { indexFirst = distance(stations.begin(), existFirst); }
			else {
				string err = string("There is no station with the name: " + firstName);
				throw err;
			}
			if (secondName != "") {
				auto existSecond = find_if(stations.begin(), stations.end(), [&](const Workstation* src) { return (src->getItemName() == secondName); });
				if (existSecond != stations.end()) { indexSecond = distance(stations.begin(), existSecond);}
				else {
					string err = string("There is no station with the name: " + secondName);
					throw err;
				}
				if (secondName == firstName) {
					string err = string("The first and second stations are the same for station: " + secondName);
					throw err;
				}
				stations[indexFirst]->setNextStation(stations[indexSecond]);
			}
			else {
				stations[indexFirst]->setNextStation(nullptr);
			}
			m_activeLine.push_back(stations[indexFirst]);
			}
			else {
				throw string("The file is empty!");
			}
		}
		auto noLast = none_of(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* src) {return src->getNextStation() == nullptr; });
		if (noLast) {
			throw string("There is no possible last station in the file");
		}
		//Compare two vectors of names to find the different element
		sort(firstStationNames.begin(), firstStationNames.end());
		sort(secondStationNames.begin(), secondStationNames.end());
		std::set_difference(firstStationNames.begin(), firstStationNames.end(), secondStationNames.begin(), secondStationNames.end(), std::back_inserter(difference));
		if (difference.size() > 1) {
			throw string("There is more than one potential starting station in the file");
		}
		else if (difference.size() == 0){
			throw string("There is no possible starting station in the file");
		}
		else {
			string itemName = difference.front();
			int firstStationIndex = 0;
			auto firstLocator = find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* src) { return (src->getItemName() == itemName); });
			firstStationIndex = std::distance(m_activeLine.begin(), firstLocator);
			m_firstStation = m_activeLine[firstStationIndex];
		}
	}
	void LineManager::reorderStations() {
		iter_swap(find_if(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* ws) {return ws->getItemName() == m_firstStation->getItemName(); }), m_activeLine.begin());
		int foundIndex = 0;
		bool stop = false;
		for (auto i = 0u; i < m_activeLine.size() - 1; i++) {
			if (m_activeLine[i]->getNextStation() != m_activeLine[i + 1]) {
				stop = false;
				for (size_t y = i + 2; y < m_activeLine.size() && !stop; y++) {
					if (m_activeLine[i]->getNextStation() == m_activeLine[y]) {
						foundIndex = y;
						stop = true;
					}
				}
				swap(m_activeLine[i + 1], m_activeLine[foundIndex]);
			}
		}
	}
	bool LineManager::run(ostream& os) {
		bool removed = false;
		static int count = 1;
		os << "Line Manager Iteration: " << count << endl;
		if (g_pending.size() != 0) {
		*m_firstStation += move(g_pending.front());
		g_pending.pop_front();
		}
		for (auto i = 0u; i < m_activeLine.size(); i++) {
			m_activeLine[i]->fill(os);
		}
		for (auto i = 0u; i < m_activeLine.size(); i++) {
			removed = m_activeLine[i]->attemptToMoveOrder();
			if (removed) { m_cntCustomerOrder--; }
		}
		count++;
		return (m_cntCustomerOrder == 0);
	}
	void LineManager::display(ostream& os) const {
		for (auto i = 0u; i < m_activeLine.size(); i++) {
			m_activeLine[i]->display(os);
		}
	}
}