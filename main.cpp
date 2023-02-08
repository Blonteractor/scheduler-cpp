#include <iostream>
#include <algorithm>
#include "process.hpp"    

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

    auto p1 = new Process(0, 10);
    auto p2 = new Process(1, 6);
    auto p3 = new Process(3, 2);
    auto p4 = new Process(5, 4);
    processes.push_back(p1);
    processes.push_back(p2);
    processes.push_back(p3);
    processes.push_back(p4);

    std::cout << "Shortest remaining time first: " << std::endl;
    auto result = shortestRemainingTimeFirst(processes);
    std::cout << "Total TAT: " << result.totalTurnAroundTime << "\tTotal WT: " << result.totalWaitTime << std::endl;
    std::cout << "Average TAT: " << result.avgTurnAroundTime << "\tAverage WT: " << result.avgWaitTime;

    std::for_each(processes.begin(), processes.end(), [](Process* p) { p->reset(); });

    std::cout << "\n\nFirst come first serve: " << std::endl;
    result = firstComeFirstServe(processes);
    std::cout << "Total TAT: " << result.totalTurnAroundTime << "\tTotal WT: " << result.totalWaitTime << std::endl;
    std::cout << "Average TAT: " << result.avgTurnAroundTime << "\tAverage WT: " << result.avgWaitTime;
}
