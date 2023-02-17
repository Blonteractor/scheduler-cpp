#include <iostream>
#include <algorithm>
#include "../process.h"

SchedulerResult Process::firstComeFirstServe(ProcessList& processes) {
    int tick = 0;
    GanttChart ganttChart;
    while (!std::all_of(processes.begin(), processes.end(), [](Process* p) { return p->isFinished(); })) {
        for (auto&& process : processes) {
            if (process->arrivalTime <= tick && !process->isFinished())
                process->state = Ready;
        }

        auto processToRun = std::min_element(processes.begin(), processes.end(), [](Process* p1, Process* p2) {
            if (!(p1->isReady() && p2->isReady())) return p1->isReady();

            if (p1->arrivalTime == p2->arrivalTime)
                return p1->burstTime < p2->burstTime;
            else
                return p1->arrivalTime < p2->arrivalTime;
            });

        if (!(*processToRun)->isReady()) continue;

        (*processToRun)->runTillEnd();
        auto node = new GanttNode;
        node->process = *processToRun;
        node->begin = tick;
        tick += (*processToRun)->burstTime;
        node->end = tick;

        (*processToRun)->exitTime = tick;
        ganttChart.push(node);
        // std::cout << "Process(" << (*processToRun)->arrivalTime << ", " << (*processToRun)->burstTime << ") finished at " << tick << std::endl;
    }

    return Process::computeResult(processes, ganttChart);
}
