// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 20/11/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField;

CustomerOrder::CustomerOrder(const std::string& input) {
	Utilities ut;
	bool more = true;
	size_t pos = 0;
	m_name = ut.extractToken(input, pos, more);
	m_product = ut.extractToken(input, pos, more);

	size_t mark_pos = pos;
	while (more) {
		ut.extractToken(input, pos, more);
		++m_cntItem;
	}
	--m_cntItem;
	more = true;
	size_t i = 0;
	m_lstItem = new ItemInfo * [m_cntItem];
	while (more && i < m_cntItem) {
		m_lstItem[i] = new ItemInfo(ut.extractToken(input, mark_pos, more));
		++i;
	}

	m_widthField = (m_widthField > ut.getFieldWidth()) ? m_widthField : ut.getFieldWidth();
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
	m_cntItem = 0;
	m_lstItem = nullptr;
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
	if (this != &src) {
		if (m_cntItem > 0)
		{
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}
		else
			delete[] m_lstItem;

		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;

		src.m_name = "";
		src.m_product = "";
		src.m_lstItem = nullptr;
		src.m_cntItem = 0;
	}

	return *this;
}

CustomerOrder::~CustomerOrder() {
	//for (size_t i = 0; i < m_cntItem; ++i) {
	//	delete m_lstItem[i];
	//}
	delete[] m_lstItem;
}

bool CustomerOrder::getItemFillState(std::string theItem) const {
	for (size_t i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_itemName == theItem)
			return m_lstItem[i]->m_fillState;
	}
	return true;
}

bool CustomerOrder::getOrderFillState() const {
	for (size_t i = 0; i < m_cntItem; ++i) {
		if (!m_lstItem[i]->m_fillState)
			return false;
	}
	return true;
}

void CustomerOrder::fillItem(Item& item, std::ostream& out) {
	for (size_t i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_itemName == item.getName()) {
			if (item.getQuantity() > 0) {
				item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				out << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				out << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& out) const {
	out << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; ++i) {
		out << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber 
			<< std::setfill(' ') << "] " << std::setw(m_widthField) 
			<< std::left << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_fillState)
			out << "FILLED";
		else out << "MISSING";
		out << std::endl;
	}
}