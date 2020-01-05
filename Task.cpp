// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 01/12/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Task.h"

Task::Task(const std::string& input) : Item(input) {
	m_pNextTask = nullptr;
}

void Task::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		if (!(--m_orders.end())->getItemFillState(this->getName())) {
			(--m_orders.end())->fillItem(*this, os);
		}
	}
}

bool Task::moveTask() {
	if (m_orders.empty())
		return false;
	else {
		if ((--m_orders.end())->getItemFillState(getName()) && m_pNextTask != nullptr) {
			*m_pNextTask += std::move(*(--m_orders.end()));
			m_orders.erase(--m_orders.end());
		}
		return true;
	}
}

void Task::setNextTask(Task& nextTask) {
	delete m_pNextTask;
	m_pNextTask = &nextTask;
}

bool Task::getCompleted(CustomerOrder& order) {
	if (m_orders.empty())
		return false;
	else {
		if (m_orders.back().getOrderFillState()) {
			order = std::move(*(--m_orders.end()));
			m_orders.erase(--m_orders.end());
			return true;
		}
		else
		return false;
	}
}

void Task::validate(std::ostream& os) {
	if (m_pNextTask == nullptr)
		os << getName() << " --> END OF LINE\n";
	else
	{
		os << getName() << " --> " << m_pNextTask->getName() << std::endl;
	}
}

Task& Task::operator+=(CustomerOrder && order) {
	m_orders.insert(m_orders.begin(), std::move(order));
	return *this;
}

Task::~Task() {
	m_pNextTask = nullptr;
	delete m_pNextTask;
}

const Task* Task::getNextTask() const {
	return m_pNextTask;
}