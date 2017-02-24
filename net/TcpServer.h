//
// Created by had on 2/24/17.
//

#ifndef MUDUO_TCPSERVER_H
#define MUDUO_TCPSERVER_H

#include <memory>
#include <netinet/in.h>
#include <functional>
#include "../uncopyable.h"

using namespace std;

class Acceptor;
class EventLoop;

class TcpServer : uncopyable{
public:
    typedef function<void()> ConnectionCallback;
    typedef function<void()> MessageCallback;
    typedef function<void()> WriteCompleteCallback;

public:
    TcpServer(EventLoop* loop, sockaddr_in addr);
    ~TcpServer();

    void start();

private:
    void newConnection(int connfd, sockaddr_in peeraddr);

private:
    EventLoop * loop_;
    unique_ptr<Acceptor> acceptorptr_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
};


#endif //MUDUO_TCPSERVER_H
