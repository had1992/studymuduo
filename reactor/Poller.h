//
// Created by had on 2/14/17.
//

#ifndef MUDUO_POLLER_H
#define MUDUO_POLLER_H

#include <vector>
#include <map>
#include "EventLoop.h"
#include "../tools/Timestamp.h"

using namespace std;

struct pollfd;
class Channel;

//IO多路复用
class Poller : uncopyable{
public:
    typedef vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    ~Poller();

    //Polls the I/O events
    //Must be called in the loop thread
    Timestamp poll(int timeoutMs, ChannelList* aactiveChannels);

    ///Changes the interested I/O events.
    ///Must be calles in the loop thread
    void updateChannel(Channel* channel);

    void removeChannel(Channel* channel);

    void assertInLoopThread(){ownerLoop_->assertInLoopThread();}

private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef vector<struct pollfd> PollFdList;
    typedef map<int, Channel*> ChannelMap;

    EventLoop* ownerLoop_;
    PollFdList pollfds_;//监视fd列表，传入poll()函数用
    ChannelMap channels_;//活动通道，激活注册的回调函数
};


#endif //MUDUO_POLLER_H
