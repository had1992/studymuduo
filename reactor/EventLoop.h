//
// Created by had on 2/13/17.
//

#ifndef MUDUO_EVENTLOOP_H
#define MUDUO_EVENTLOOP_H

#include <memory>
#include <zconf.h>
#include <vector>
#include "../uncopyable.h"

using namespace std;

class Poller;
class Channel;

class EventLoop : public uncopyable{
public:
    EventLoop();//如果本线程已经存在一个对象，则输出错误日志
    ~EventLoop();

    void loop();//运行事件循环

    inline void quit(){quit_ = true;}

    void updateChannel(Channel * channel);//添加新通道或者更新通道信息

    void removeChannel(Channel * channel);

    void assertInLoopThread();//判断该对象是否是在本线程创建

    inline bool isInLoopThread() const;

    EventLoop* getEventLoopOfCurrentThread();

private:
    typedef vector<Channel*> ChannelList;

    void abortNotInLoopThread();

    bool looping_;//判断当前是否正在运行loop（）
    bool quit_;
    const pid_t threadId_;
    shared_ptr<Poller> poller_;
    ChannelList activeChannels_;
};


#endif //MUDUO_EVENTLOOP_H
