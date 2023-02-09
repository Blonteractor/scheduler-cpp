#pragma once
#include <vector>

enum ProcessState { NotInSystem, Ready, Finished };

class Process;
typedef std::vector<Process*> ProcessList;

struct SchedulerResult {
    int totalTurnAroundTime;
    int totalWaitTime;
    float avgWaitTime;
    float avgTurnAroundTime;
};

class Process {
private:
    int arrivalTime;
    int burstTime;
    int exitTime;
    int progress;
    ProcessState state;
public:
    Process(int arrivalTime, int burstTime);

    void reset();

    int getArrivalTime() const;
    int turnAroundTime() const;
    int waitTime() const;
    int timeToCompletion() const;
    bool isFinished() const;
    bool isReady() const;
    bool isInSystem() const;

    ProcessState getState() const;

    void setState(ProcessState state);

    int runFor(int time);
    int runOnce();
    int runTillEnd();

    static SchedulerResult computeResult(ProcessList& processes);

    friend SchedulerResult firstComeFirstServe(ProcessList& processes);
    friend SchedulerResult shortestRemainingTimeFirst(ProcessList& processes);
    friend SchedulerResult shortestJobFirst(ProcessList& processes);
    friend SchedulerResult highestPriorityFirst(ProcessList& processes);
    friend SchedulerResult highestPriorityFirstPreemptive(ProcessList& processes);
    friend SchedulerResult roundRobin(ProcessList& processes, int quantum);
};
