// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 15/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <sstream>
#include "Utilities.h"

	void Utilities::setFieldWidth(size_t fieldWidth) {
		m_widthField = fieldWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string temp = "";
		std::string l_str = str;
		l_str.erase(0, next_pos);
		std::stringstream ss(l_str);
		std::getline(ss, temp, m_delimiter);
		next_pos += (temp.length() + 1);
		temp.erase(0, temp.find_first_not_of(" "));
		temp.erase(temp.find_last_not_of(" ") + 1);
		if (temp != "") {
			more = true;
			if (m_widthField < temp.length())
				setFieldWidth(temp.length());
			return temp;
		}
		else {
			more = false;
			//throw -1;
			return "";
		}
	}

	char Utilities::m_delimiter;

	void Utilities::setDelimiter(const char denim) {
		m_delimiter = denim;
	}

	const char Utilities::getDelimiter() const {
		return m_delimiter;
	}