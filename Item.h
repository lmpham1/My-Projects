// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 15/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

	class Item {
		std::string m_name;
		std::string m_description;
		size_t		m_serialNumber;
		size_t		m_quantity;
		static size_t m_widthField;

	public:
		Item() : m_name(""), m_description(""), m_serialNumber(0), m_quantity(0) {};
		Item(const std::string);
		const std::string& getName() const;
		const unsigned int getSerialNumber();
		const unsigned int getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

#endif