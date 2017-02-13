//
// Created by had on 2/13/17.
//

#include <syscall.h>
#include <assert.h>
#include "EventLoop.h"

//__thread关键字保证该资源每个线程独有。
__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop():looping_(false),threadId_((pid_t)syscall(syscall(__NR_gettid))) {
    //todo print log
    if(t_loopInThisThread){
        //todo print log
    } else {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    assert(!looping_);
    t_loopInThisThread = NULL;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return t_loopInThisThread;
}

void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    sleep(1);
    //todo print log
    looping_ = false;
}

void EventLoop::assertInLoopThread() {
    if(!isInLoopThread()){
        abortNotInLoopThread();
    }
}

inline bool EventLoop::isInLoopThread() const {
    return threadId_ == syscall(__NR_gettid);
}

void EventLoop::abortNotInLoopThread() {
    _exit(0);
}
