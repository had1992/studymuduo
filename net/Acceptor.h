//
// Created by had on 2/24/17.
//

#ifndef MUDUO_ACCEPTOR_H
#define MUDUO_ACCEPTOR_H

#include <netinet/in.h>
#include "../uncopyable.h"
#include "../reactor/Channel.h"
#include "Socket.h"

class EventLoop;

class Acceptor : uncopyable{
public:
    typedef function<void(int, sockaddr_in)> NewConnectionCallback;

    Acceptor(EventLoop* loop, sockaddr_in listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb)
    { newConnectionCallback_ = cb; }

    bool listenning() const { return listenning_; }
    void listen();

private:
    void handleRead();

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;
    int idleFd_;
};


#endif //MUDUO_ACCEPTOR_H
