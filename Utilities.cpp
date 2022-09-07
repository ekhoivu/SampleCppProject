/*
Name: Khoi Vu
Seneca Student ID: 124611203
Seneca email: kvu8@myseneca.ca
Date of completion: July 21st, 2022

I confirm that I am the only author of this file
and the content was created entirely by me.
*/

#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter = ',';
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		unsigned int index;
		string temp, token;
		temp = str.substr(next_pos);
		index = temp.find(m_delimiter);
		if (index == 0) {
			more = false;
			throw string("No token");
		}
		else if (index == 1) {
			more = false;
			throw string("Delimiter at next_pos");
		}
		else {
			token = temp.substr(0, index);
			trimSpace(token);
			if (token.length() > m_widthField) {
				m_widthField = token.length();
			}
			if (index < temp.length()) {
				more = true;
				next_pos += index + 1;
			}
			else {
				more = false;
			}
		}
		return token;
	}
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
	void trimSpace(string& input) {
		if (input.length()) {
			unsigned int findSpace = 0;
			bool done = false;
			do {
				findSpace = input.find_first_of(" ");
				if (findSpace == 0) {
					input.erase(0, 1);
				}
				else {
					done = true;
				}
			} while (!done);
			done = false;
			do {
				findSpace = input.find_last_of(" ");
				if (findSpace == input.length() - 1) {
					input.erase(input.length() - 1, 1);
				}
				else {
					done = true;
				}
			} while (!done);
		}
	}
}