//
// Created by had on 2/24/17.
//

#include "TcpServer.h"
#include "Acceptor.h"

TcpServer::TcpServer(EventLoop* loop, sockaddr_in addr)
        :loop_(loop),
         acceptorptr_(new Acceptor(loop_,addr,false)) {
    acceptorptr_->setNewConnectionCallback(::bind(TcpServer::newConnection,this,_1,_2));
}

TcpServer::~TcpServer() {

}

void TcpServer::start() {

}

void TcpServer::newConnection(int connfd, sockaddr_in peeraddr) {
    EventLoop* ioloop;

}
