// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 15/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Item.h"
#include "Utilities.h"

	size_t Item::m_widthField;

	Item::Item(const std::string str) {
		Utilities ut;
		bool more = true;
		size_t pos = 0;
		m_name = ut.extractToken(str, pos, more);
		m_widthField = (m_widthField > ut.getFieldWidth()) ? m_widthField : ut.getFieldWidth();
		m_serialNumber = std::stoi(ut.extractToken(str, pos, more));
		m_quantity = std::stoi(ut.extractToken(str, pos, more));
		m_description = ut.extractToken(str, pos, more);
	}

	const std::string& Item::getName() const {
		return m_name;
	}

	const unsigned int Item::getSerialNumber() {
		return m_serialNumber++;
	}

	const unsigned int Item::getQuantity() const {
		return m_quantity;
	}

	void Item::updateQuantity() {
		if (m_quantity - 1 >= 0)
			--m_quantity;
	}

	void Item::display(std::ostream& out, bool full) const {
		
		out << std::setw(m_widthField) << std::left << m_name
			<< std::right << " [" << std::setfill('0') << std::setw(6) 
			<< m_serialNumber << std::setfill(' ') << "]";
		
		if (full)
			out << " Quantity: " << std::setw(m_widthField) << std::left
			<< m_quantity << " Description: " << m_description;
		out << std::endl;
	}