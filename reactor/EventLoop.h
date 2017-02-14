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
    EventLoop();//如果本线程已经存在一个对象，则输出错误日志
    ~EventLoop();

    void loop();//运行事件循环

    void assertInLoopThread();//判断该对象是否是在本线程创建

    inline bool isInLoopThread() const;

    EventLoop* getEventLoopOfCurrentThread();

private:
    void abortNotInLoopThread();

    bool looping_;//判断当前是否正在运行loop（）
    const pid_t threadId_;
};


#endif //MUDUO_EVENTLOOP_H
