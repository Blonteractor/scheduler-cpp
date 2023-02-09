#include <queue>
#include <algorithm>
#include <iostream>
#include <optional>
#include "process.hpp"

typedef std::queue<Process*> ProcessQueue;

SchedulerResult roundRobin(ProcessList& processes, int quantum) {
    ProcessQueue pq;
    Process* lastUnfinishedProcess{};
    Process* processToRun;

    std::sort(processes.begin(), processes.end(), [](Process* p1, Process* p2) { return p1->arrivalTime < p2->arrivalTime; });

    int tick = 0;
    while (!std::all_of(processes.begin(), processes.end(), [](Process* p) { return p->isFinished(); })) {
        for (auto&& process : processes) {
            if (process->arrivalTime <= tick && !process->isFinished() && process != lastUnfinishedProcess) {
                process->state = Ready;
                pq.push(process);
            }
        }

        if (lastUnfinishedProcess != nullptr) {
            pq.push(lastUnfinishedProcess);
            lastUnfinishedProcess = nullptr;
        }

        processToRun = pq.front();
        pq.pop();

        processToRun->runFor(quantum);
        tick += quantum;

        if (processToRun->isFinished()) {
            std::cout << "Process(" << processToRun->arrivalTime << ", " << processToRun->burstTime << ") finished at " << tick << std::endl;
            processToRun->exitTime = tick;
            lastUnfinishedProcess = nullptr;
        }
        else {
            lastUnfinishedProcess = processToRun;
        }
    }

    return Process::computeResult(processes);
}