//
// Created by had on 2/15/17.
//

#include "TimerQueue.h"
#include "Timer.h"
#include "TimerId.h"


TimerQueue::TimerQueue(EventLoop *loop):
        loop_(loop), timerfd_(-1), timerfdChannel_(loop_,timerfd_){

}

TimerQueue::~TimerQueue() {

}

TimerId TimerQueue::addTimer(const TimerCallback &cb, Timestamp when, double interval) {
    timerfdChannel_.setRaedCallback(cb);
}

void TimerQueue::cancel(TimerId timerId) {

}

void TimerQueue::handleRead() {

}

vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now) {
    return vector<TimerQueue::Entry>();
}

void TimerQueue::reset(const vector<Entry> &expired, Timestamp now) {

}

bool TimerQueue::insert(Timer *timer) {
    return false;
}
