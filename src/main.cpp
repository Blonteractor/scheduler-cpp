#include <iostream>
#include "process.h"

typedef std::string string;

void performAlgo(string title, SchedulerResult(*algo)(ProcessList&), ProcessList& processes) {
    std::cout << "\n\n" << title << ":" << std::endl;
    auto result = algo(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);
}

void performAlgo(string title, SchedulerResult(*algo)(ProcessList&, int), ProcessList& processes, int tq) {
    std::cout << "\n\n" << title << ":" << std::endl;
    auto result = algo(processes, tq);
    Process::printResult(result);
    Process::resetProcessQueue(processes);
}

int main() {
    ProcessList processes = {
        new Process(0, 10, 2),
        new Process(1, 6, 5),
        new Process(3 ,2, 3),
        new Process(5, 4, 1)
    };

    performAlgo("First come first serve", Process::firstComeFirstServe, processes);
    performAlgo("Shortest job first", Process::shortestJobFirst, processes);
    performAlgo("Shortest remaining time first", Process::shortestRemainingTimeFirst, processes);
    performAlgo("Highest priority first (Non-preemptive)", Process::highestPriorityFirst, processes);
    performAlgo("Highest priority first (Preemptive)", Process::highestPriorityFirstPreemptive, processes);
    performAlgo("Round robin", Process::roundRobin, processes, 2);
}
