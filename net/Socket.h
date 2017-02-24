//
// Created by had on 2/24/17.
//

#ifndef MUDUO_SOCKET_H
#define MUDUO_SOCKET_H


class Socket {
public:
    explicit Socket(int fd);
    ~Socket();
    int accept(sockaddr_in * addr);
    void listen();
    int getfd(){return fd_;};
private:
    int fd_;

};


#endif //MUDUO_SOCKET_H
