//
// Created by had on 2/15/17.
//

#ifndef MUDUO_TIMERQUEUE_H
#define MUDUO_TIMERQUEUE_H

#include <functional>
#include <set>
#include <vector>
#include "../uncopyable.h"
#include "../tools/Timestamp.h"

using namespace std;

class EventLoop;
class TimerId;
class Timer;
class Channel;

class TimerQueue : uncopyable{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue(){}

    TimerId addTimer(const TimerCallback& cb, Timestamp when, double interval);

private:
    //FIXME: use unique_ptr<Timer> instead of raw pointers.
    typedef function<void()> TimerCallback;
    typedef pair<Timestamp, Timer*> Entry;
    typedef set<Entry> TimerList;

    void handleRead();
    vector<Entry> getExpired(Timestamp now);
    void reset(const vector<Entry>& expired, Timestamp now);

    bool insert(Timer* timer);

    EventLoop* loop_;
    const int timerfd_;
    Channel timerfdChannel_;
    TimerList timers_;
};


#endif //MUDUO_TIMERQUEUE_H
