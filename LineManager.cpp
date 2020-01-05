// Name: Le Minh Pham
// Seneca Student ID: 107259186
// Seneca email: lmpham1@myseneca.ca
// Date of completion: 01/12/2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& file, std::vector<Task*>& tasks, std::vector<CustomerOrder>& orders) {
	Utilities ut;
	
	std::ifstream theFile(file, std::ios::in);

	if (!theFile)
		throw std::string("Unable to open [" + file + "] file.");

	std::string line;
	ut.setDelimiter('|');
	while (!theFile.eof()) {
		std::getline(theFile, line);

		bool more = true;
		size_t pos = 0;
		std::string currentTaskName = ut.extractToken(line, pos, more);
		std::string nextTaskName = ut.extractToken(line, pos, more);
		if (nextTaskName != "") {
			for (auto i : tasks) {
				if (i->getName() == currentTaskName) {
					for (auto j : tasks)
						if (j->getName() == nextTaskName) {
							i->setNextTask(*j);
							break;
						}
					break;
				}
			}
		}		
	}
	theFile.close();

	for (auto i : tasks) {
		AssemblyLine.push_back(i);
	}
	std::for_each(orders.begin(), orders.end(), [&](CustomerOrder& theOrder) {
		ToBeFilled.push_front(std::move(theOrder));
		++m_cntCustomerOrder;
	});
}

bool LineManager::run(std::ostream& os) {
	if (Completed.size() != m_cntCustomerOrder) {
		if (!ToBeFilled.empty()) {
			Task* start = nullptr;
			for (auto task : AssemblyLine)
			{
				bool flag = false;
				for (auto task2 : AssemblyLine)
				{
					if (task2->getNextTask() == task)
						flag = true;
				}
				if (!flag) {
					start = task;
				}
			}

			*start += std::move(ToBeFilled.back());
			ToBeFilled.pop_back();
		}
		for (auto task : AssemblyLine) {
			task->runProcess(os);
		}
		for (auto task : AssemblyLine) {
			if (task->getNextTask() == nullptr) {
				CustomerOrder done;
				if (task->getCompleted(done))
					Completed.push_back(std::move(done));
			}
			task->moveTask();
		}
		return false;
	}
	else
		return true;
}

void LineManager::displayCompleted(std::ostream& os) const {
	std::for_each(Completed.begin(), Completed.end(), [&](const CustomerOrder& order) {
		order.display(os);
	});
}

void LineManager::validateTasks() const {
	for (auto i : AssemblyLine) {
		i->validate(std::cout);
	}
}