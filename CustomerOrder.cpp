/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: July 24th, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder() {
		m_name = {};
		m_product = {};
		m_cntItem = {};
		m_lstItem = nullptr;
	}
	void CustomerOrder::deallo() {
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(const std::string& src) : CustomerOrder() {
		Utilities util;
		bool more = true;
		size_t pos = 0u;
		string temp[101];
		size_t count = 0;
		m_name = util.extractToken(src, pos, more);
		m_product = util.extractToken(src, pos, more);
		do {
			temp[count] = util.extractToken(src, pos, more);
			count++;
		} while (more);
		m_lstItem = new Item * [count];
		for (auto i = 0u; i < count; i++) {
			m_lstItem[i] = new Item(temp[i]);
		}
		m_cntItem = count;
		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw string("CustomerOrder should not be copied!");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept : CustomerOrder() {
		*this = move(src);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			deallo();
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
			m_name = src.m_name;
			src.m_name = {};
			m_product = src.m_product;
			src.m_product = {};
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		deallo();
	}
	bool CustomerOrder::isOrderFilled() const {
		bool filled = true;
		for (auto i = 0u; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				filled = false;
			}
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool filled = true;
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				filled = false;
			}
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool cont = true;
		for (auto i = 0u; i < m_cntItem && cont; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && station.getQuantity() >= 1) {
				m_lstItem[i]->m_isFilled = true;
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				station.updateQuantity();
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				cont = false;
			}
			else if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && station.getQuantity() == 0) {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (auto i = 0u; i < m_cntItem; i++) {
			os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] " << left << setfill(' ') << setw(m_widthField) << left << m_lstItem[i]->m_itemName << "   - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << endl;
			}
			else {
				os << "TO BE FILLED" << endl;
			}
		}
	}
}