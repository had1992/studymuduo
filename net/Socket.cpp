//
// Created by had on 2/24/17.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <cstdio>
#include "Socket.h"

Socket::Socket(int fd) : fd_(fd) {sockaddr_in * addr

}

Socket::~Socket() {
    ::close(fd_);
}

int Socket::accept(sockaddr_in * addr) {
    return ::accept(fd_, static_cast<sockaddr*>(addr),sizeof(sockaddr_in));
}

void Socket::listen() {
    int ret = ::listen(fd_, SOMAXCONN);
    if (ret < 0)
    {
        std::perror("listen");
    }
}
