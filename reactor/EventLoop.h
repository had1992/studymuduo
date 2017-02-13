//
// Created by had on 2/13/17.
//

#ifndef MUDUO_EVENTLOOP_H
#define MUDUO_EVENTLOOP_H

#include <zconf.h>
#include "../uncopyable.h"

//using namespace std;

class EventLoop : public uncopyable{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread();

    inline bool isInLoopThread() const;

    EventLoop* getEventLoopOfCurrentThread();

private:
    void abortNotInLoopThread();

    bool looping_;
    const pid_t threadId_;
};


#endif //MUDUO_EVENTLOOP_H
