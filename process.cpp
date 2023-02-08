#include "process.hpp"

Process::Process(int arrivalTime, int burstTime) {
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    this->exitTime = 0;
    this->progress = 0;
    this->state = NotInSystem;
}

void Process::reset() {
    this->exitTime = 0;
    this->progress = 0;
    this->state = NotInSystem;
}

int Process::getArrivalTime() const {
    return this->arrivalTime;
}

int Process::turnAroundTime() const {
    return this->exitTime - this->arrivalTime;
}

int Process::waitTime() const {
    return this->turnAroundTime() - this->burstTime;
}

ProcessState Process::getState() const {
    return this->state;
}

void Process::setState(ProcessState state) {
    this->state = state;
}

int Process::timeToCompletion() const {
    return this->burstTime - this->progress;
}

int Process::runFor(int time) {
    this->progress += time;

    if (this->timeToCompletion() == 0)
        this->state = Finished;

    return this->progress;
}

bool Process::isFinished() const {
    return this->state == Finished;
}

bool Process::isReady() const {
    return this->state == Ready;
}

bool Process::isInSystem() const {
    return this->state != NotInSystem;
}

int Process::runOnce() {
    return this->runFor(1);
}

int Process::runTillEnd() {
    this->progress = this->burstTime;
    this->state = Finished;

    return this->progress;
}

SchedulerResult Process::computeResult(ProcessList& processes) {
    int totalTurnAroundTime = 0;
    int totalWaitTime = 0;
    for (auto&& process : processes) {
        totalTurnAroundTime += process->turnAroundTime();
        totalWaitTime += process->waitTime();
    }

    SchedulerResult s;
    s.totalWaitTime = totalWaitTime;
    s.totalTurnAroundTime = totalTurnAroundTime;
    s.avgTurnAroundTime = (float)totalTurnAroundTime / processes.size();
    s.avgWaitTime = (float)totalWaitTime / processes.size();
    return s;
}
