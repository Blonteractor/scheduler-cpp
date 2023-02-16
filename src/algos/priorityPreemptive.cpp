#include <iostream>
#include <algorithm>
#include "../process.h"

SchedulerResult highestPriorityFirstPreemptive(ProcessList& processes) {
    int tick = 0;
    GanttChart chart;
    while (!std::all_of(processes.begin(), processes.end(), [](Process* p) { return p->isFinished(); })) {
        for (auto&& process : processes) {
            if (process->arrivalTime <= tick && !process->isFinished())
                process->state = Ready;
        }

        auto processToRun = std::min_element(processes.begin(), processes.end(), [](Process* p1, Process* p2) {
            if (!(p1->isReady() && p2->isReady())) return p1->isReady();

            if (p1->priority == p2->priority)
                return p1->arrivalTime < p2->arrivalTime;
            else
                return p1->priority > p2->priority;
            });

        if (!(*processToRun)->isReady()) continue;

        auto node = new GanttNode;
        node->process = *processToRun;
        node->begin = tick;

        (*processToRun)->runOnce();
        tick++;
        node ->end = tick;

        chart.push(node);
        
        if ((*processToRun)->isFinished()) {
            // std::cout << "Process(" << (*processToRun)->arrivalTime << ", " << (*processToRun)->burstTime << ") finished at " << tick << std::endl;
            (*processToRun)->exitTime = tick;
        }
    }

    return Process::computeResult(processes, chart);
}
