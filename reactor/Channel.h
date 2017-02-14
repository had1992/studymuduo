//
// Created by had on 2/14/17.
//

#ifndef MUDUO_CHANNEL_H
#define MUDUO_CHANNEL_H

#include <functional>
#include "../uncopyable.h"

using namespace std;

class EventLoop;//前置声明，这样可以不用include"EventLoop.h"

//每个Channel对象自始至终只属于一个EventLoop
class Channel :uncopyable{
public:
    typedef function<void()> EventCallback;
    Channel(EventLoop* loop, int fd);//每个对象管一个fd

    void handleEvent();//由EventLoop.loop()调用

    inline void setRaedCallback(const EventCallback& cb){readCallback_ = cb;};//设置回调函数
    inline void setWriteCallback(const EventCallback& cb){writeCallback_ = cb;};
    inline void setErrorCallback(const EventCallback& cb){errorCallback_ = cb;};

    inline void set_revents(int revt){revents_ = revt;}//设置目前活动事件

    inline int fd() const {return fd_;}
    inline int events() const {return events_;}
    inline bool isNoneEvent() const {return events_ == kNoneEvent;}

    void enableReading() {events_ |= kReadEvent;update();}//设置关心事件
    void enableWriting() {events_ |= kWriteEvent;update();}
    void disableWriting() {events_ &= ~kWriteEvent;update();}
    void disableAll() {events_ = kNoneEvent;update();}

    inline void set_index(int idx){index_ = idx;}
    inline int index(){return index_;}

    inline EventLoop* ownerLoop() {return loop_;}

private:
    void update();
    static const int kNoneEvent;//poller事件类型，cpp中定义
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    const int fd_;
    int events_;//关心的事件
    int revents_;//目前活动事件
    int index_;//used by Poller

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};

#endif //MUDUO_CHANNEL_H
