#include <iostream>
#include <algorithm>
#include "process.h"
#include <iostream>

int main() {
    ProcessList processes;
    // int numberOfProcess;
    // std::cout << "Enter number of processes: ";
    // std::cin >> numberOfProcess;

    // for (int i = 0; i < numberOfProcess; i++) {
    // 	int at;
    // 	int bt;
    // 	std::cout << "Enter arrival and burst time of process " << i + 1 << ": ";
    // 	std::cin >> at >> bt;
    // 	auto p = new Process(at, bt);
    // 	processes.push_back(p);
    // }

    SchedulerResult result;
    auto p1 = new Process(0, 10, 2);
    auto p2 = new Process(1, 6, 5);
    auto p3 = new Process(3, 2, 3);
    auto p4 = new Process(5, 4, 1);
    processes.push_back(p1);
    processes.push_back(p2);
    processes.push_back(p3);
    processes.push_back(p4);

    std::cout << "\n\nFirst come first serve: " << std::endl;
    result = firstComeFirstServe(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);

    std::cout << "\n\nShortest job first: " << std::endl;
    result = shortestJobFirst(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);

    std::cout << "\n\nShortest remaining time first: " << std::endl;
    result = shortestRemainingTimeFirst(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);

    std::cout << "\n\nHighest priority first non-preemptive: " << std::endl;
    result = highestPriorityFirst(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);

    std::cout << "\n\nHighest priority first preemptive: " << std::endl;
    result = highestPriorityFirstPreemptive(processes);
    Process::printResult(result);
    Process::resetProcessQueue(processes);

    std::cout << "\n\nRound Robin: " << std::endl;
    result = roundRobin(processes, 2);
    Process::printResult(result);
    Process::resetProcessQueue(processes);
}
