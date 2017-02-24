//
// Created by had on 2/24/17.
//

#include "Acceptor.h"
#include <fcntl.h>
#include "../reactor/EventLoop.h"

Acceptor::Acceptor(EventLoop *loop, sockaddr_in listenAddr, bool reuseport)
        :loop_(loop),
         acceptSocket_(::socket(0,0,0)),//todo ......
         acceptChannel_(loop_,acceptSocket_.getfd()),
         newConnectionCallback_(),
         listenning_(false),
         idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC)){
    acceptChannel_.setReadCallback(
            bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor() {

}

void Acceptor::listen() {
    loop_->assertInLoopThread();
    acceptSocket_.listen();
    listenning_ = true;
    acceptChannel_.enableReading();//这里包含了updateChannel
}

void Acceptor::handleRead() {
    loop_->assertInLoopThread();
    sockaddr_in addr;
    int connfd = acceptSocket_.accept(&addr);
    if (connfd > 0) {
        if (newConnectionCallback_){
            newConnectionCallback_(connfd,addr);
        }
    }else {
        ::close(connfd);
    }
}
