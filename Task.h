// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 01/12/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef TASK_H
#define TASK_H
#include <list>
#include <iostream>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	std::list<CustomerOrder> m_orders;
	Task* m_pNextTask;
public:
	Task(const std::string&);
	Task(const Task&) = delete;
	Task(const Task&&) = delete;
	Task& operator=(const Task&) = delete;
	Task& operator=(const Task&&) = delete;
	~Task();
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
	const Task* getNextTask() const;
};

#endif