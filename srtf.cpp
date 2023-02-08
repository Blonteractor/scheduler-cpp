#include <iostream>
#include <algorithm>
#include "process.hpp"

SchedulerResult shortestRemainingTimeFirst(ProcessList& processes) {
	for (int tick = 0; !std::all_of(processes.begin(), processes.end(), [](Process* p) { return p->isFinished(); }); tick++) {
		for (auto&& process : processes) {
			if (process->arrivalTime <= tick && !process->isFinished())
				process->state = Ready;
		}

		auto processToRun = std::min_element(processes.begin(), processes.end(), [](Process* p1, Process* p2) {
			if (!(p1->isReady() && p2->isReady())) return p1->isReady();

			if (p1->timeToCompletion() == p2->timeToCompletion())
				return p1->arrivalTime < p2->arrivalTime;
			else
				return p1->timeToCompletion() < p2->timeToCompletion();
			});

		if (!(*processToRun)->isReady()) continue;

		(*processToRun)->runOnce();
		if ((*processToRun)->isFinished()) {
			std::cout << "Process(" << (*processToRun)->arrivalTime << ", " << (*processToRun)->burstTime << ") finished at " << tick + 1 << std::endl;
			(*processToRun)->exitTime = tick + 1;
		}
	}

	return Process::computeResult(processes);
}