// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 20/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Item.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {};
	CustomerOrder(const std::string&);
	CustomerOrder(const CustomerOrder&) {
		throw "Copy Constructor Is Not Allowed!";
	}
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&);
	~CustomerOrder();

	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item&, std::ostream&);
	void display(std::ostream&) const;
};

#endif
