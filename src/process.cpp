#include "process.h"

Process::Process(size_t arrivalTime, size_t burstTime, size_t priority) {
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    this->priority = priority;
    this->exitTime = 0;
    this->progress = 0;
    this->state = NotInSystem;
}

void Process::reset() {
    this->exitTime = 0;
    this->progress = 0;
    this->state = NotInSystem;
}

size_t Process::getArrivalTime() const {
    return this->arrivalTime;
}

size_t Process::getPriority() const {
    return this->priority;
}

size_t Process::turnAroundTime() const {
    return this->exitTime - this->arrivalTime;
}

size_t Process::waitTime() const {
    return this->turnAroundTime() - this->burstTime;
}

ProcessState Process::getState() const {
    return this->state;
}

void Process::setState(ProcessState state) {
    this->state = state;
}

size_t Process::timeToCompletion() const {
    return this->burstTime - this->progress;
}

size_t Process::runFor(size_t time) {
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

size_t Process::runOnce() {
    return this->runFor(1);
}

size_t Process::runTillEnd() {
    this->progress = this->burstTime;
    this->state = Finished;

    return this->progress;
}

SchedulerResult Process::computeResult(ProcessList& processes) {
    size_t totalTurnAroundTime = 0;
    size_t totalWaitTime = 0;
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