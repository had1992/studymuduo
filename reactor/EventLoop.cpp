//
// Created by had on 2/13/17.
//

#include <syscall.h>
#include <assert.h>
#include <algorithm>
#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

//__thread关键字保证该资源每个线程独有。
__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop():
        looping_(false),
        threadId_((pid_t)syscall(__NR_gettid)),
        quit_(false),
        poller_(new Poller(this))
{
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
    quit_ = false;

    while(!quit_){
        activeChannels_.clear();
        int kPollTimeMs = -1;
        poller_->poll(kPollTimeMs,&activeChannels_);//获得活动fd对应的通道列表
        for_each(activeChannels_.begin(),activeChannels_.end(),[](Channel* channel){
            channel->handleEvent();
        });
    }

    //todo print log
    looping_ = false;
}

void EventLoop::updateChannel(Channel *channel) {
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel) {
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->removeChannel(channel);
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
