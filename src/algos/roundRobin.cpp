#include <queue>
#include <algorithm>
#include <iostream>
#include <optional>
#include "../process.h"

typedef std::queue<Process*> ProcessQueue;

SchedulerResult Process::roundRobin(ProcessList& processes, int quantum = 2) {
    ProcessQueue pq;
    Process* lastUnfinishedProcess{};
    Process* processToRun;
    GanttChart chart;

    std::sort(processes.begin(), processes.end(), [](Process* p1, Process* p2) { return p1->arrivalTime < p2->arrivalTime; });

    int tick = 0;
    while (!std::all_of(processes.begin(), processes.end(), [](Process* p) { return p->isFinished(); })) {
        for (auto&& process : processes) {
            if (process->arrivalTime <= tick && !process->isInSystem() && process != lastUnfinishedProcess) {
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
        processToRun->state = NotInSystem;

        auto node = new GanttNode;
        node->process = processToRun;
        node->begin = tick;

        processToRun->runFor(quantum);
        tick += quantum;
        node->end = tick;

        chart.push(node);

        if (processToRun->isFinished()) {
            // std::cout << "Process(" << processToRun->arrivalTime << ", " << processToRun->burstTime << ") finished at " << tick << std::endl;
            processToRun->exitTime = tick;
        }
        else {
            lastUnfinishedProcess = processToRun;
            lastUnfinishedProcess->state = Ready;
        }
    }

    return Process::computeResult(processes, chart, false);
}
