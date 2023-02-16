#pragma once
#include <vector>
#include <queue>

enum ProcessState { NotInSystem, Ready, Finished };
typedef std::size_t size_t;

class Process;
typedef std::vector<Process*> ProcessList;

struct GanttNode {
    size_t begin;
    size_t end;
    Process* process;
};

typedef std::queue<GanttNode*> GanttChart;

struct SchedulerResult {
    size_t totalTurnAroundTime;
    size_t totalWaitTime;
    float avgWaitTime;
    float avgTurnAroundTime;
    GanttChart ganttChart;
};

class Process {
private:
    size_t arrivalTime;
    size_t burstTime;
    size_t exitTime;
    size_t progress;
    size_t priority;
    ProcessState state;
public:
    Process(size_t arrivalTime, size_t burstTime, size_t priority = 0);

    void reset();

    size_t getArrivalTime() const;
    size_t getPriority() const;
    size_t turnAroundTime() const;
    size_t waitTime() const;
    size_t timeToCompletion() const;
    bool isFinished() const;
    bool isReady() const;
    bool isInSystem() const;

    ProcessState getState() const;

    void setState(ProcessState state);

    size_t runFor(size_t time);
    size_t runOnce();
    size_t runTillEnd();

    static SchedulerResult computeResult(ProcessList& processes, GanttChart& chart);
    static void printResult(SchedulerResult& result);
    static void resetProcessQueue(ProcessList& processes);

    friend SchedulerResult firstComeFirstServe(ProcessList& processes);
    friend SchedulerResult shortestRemainingTimeFirst(ProcessList& processes);
    friend SchedulerResult shortestJobFirst(ProcessList& processes);
    friend SchedulerResult highestPriorityFirst(ProcessList& processes);
    friend SchedulerResult highestPriorityFirstPreemptive(ProcessList& processes);
    friend SchedulerResult roundRobin(ProcessList& processes, int quantum);
};
