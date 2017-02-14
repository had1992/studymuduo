//
// Created by had on 2/14/17.
//

#include <poll.h>
#include <time.h>
#include <assert.h>
#include "Channel.h"
#include "Poller.h"

Poller::Poller(EventLoop *loop) : ownerLoop_(loop) {

}

Poller::~Poller() {

}

Timestamp Poller::poll(int timeoutMs, Poller::ChannelList *activeChannels) {
    int numEvents = ::poll(pollfds_.data(),pollfds_.size(),timeoutMs);
    Timestamp now(Timestamp::now());
    if(numEvents > 0) {
        //todo LOG_TRACE
        fillActiveChannels(numEvents,activeChannels);
    } else if(numEvents == 0) {
        //todo LOG_TRACE
    } else {
        //todo LOG_SYSERR
    }
    return now;
}

//传入一个channel，根据channel->index_值分情况处理
//index是channel对应的pollfd在pollfds中的下标值
void Poller::updateChannel(Channel *channel) {
    assertInLoopThread();//检测EventLoop是否时在本线程中运行
    //todo LOG_TRACE
    if (channel->index() < 0) {
        //a new one, add to pollfds_
        assert(channels_.find(channel->fd()) == channels_.end());//检测该通道是否存在于管理的通道哈希表中
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        pollfds_.push_back(pfd);//加入监测fd列表中
        int idx = static_cast<int>(pollfds_.size()-1);//最后一个元素的下标值
        channel->set_index(idx);
        channels_[pfd.fd]=channel;//加入通道哈希表中
    } else{
        //update existing one
        assert(channels_[channel->fd()] == channel);
        int idx = channel->index();
        assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
        struct pollfd& pfd = pollfds_[idx];//取出通道对应的事件
        assert(pfd.fd == channel->fd() || pfd.fd == -1);
        pfd.events = static_cast<short>(channel->events());//设置事件类型
        pfd.revents = 0;//将该fd对应的已发生状态清零
        if(channel->isNoneEvent()){
            pfd.fd = -1;//如果该通道不关心任何事件，将fd设为-1，这样poll函数将跳过对此fd的监测
        }
    }
}

void Poller::fillActiveChannels(int numEvents, Poller::ChannelList *activeChannels) const {
    PollFdList::const_iterator pfd = pollfds_.begin();
    for(;pfd!=pollfds_.end() && numEvents>0 ;pfd++ ){//遍历找出活动fd
        if (pfd->revents > 0) {
            --numEvents;
            ChannelMap::const_iterator ch = channels_.find(pfd->fd);
            assert(ch != channels_.end());//假如不存在对应的通道,报错
            Channel * channel = ch->second;
            assert(channel->fd() == pfd->fd);//检测该通道所管理的fd是否与活动fd相符
            channel->set_revents(pfd->revents);//设置该通道活动事件类型
            activeChannels->push_back(channel);//塞入活动通道容器中
        }
    }
}
