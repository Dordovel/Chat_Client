//
// Created by Dordovel on 09.10.2018.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H

#include <iostream>
#include "../I/IClient.h"

#ifdef _WIN32

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <inaddr.h>

#elif __linux__

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET int
#define WSAData void*

#endif


class Client:public IClient
{
    WSAData data;
    SOCKET sock;
    sockaddr_in addr_in;
    int port;
    char* address;
    int sizeAddr_in = sizeof( addr_in );
    hostent *host;
    long errorCode=0;

    char buffer[20];

    fd_set set;
    struct timeval time;

public:
    Client(char * address,int port);
    ~Client();

    bool connection() override;
    bool send_message(char *message) override;
    bool write_message() override;
    bool startClient() override;
    long getErrorCode() override;
    char* getResponse() override;
    char* getHostProperties() override;
};

#endif //UNTITLED_CLIENT_H
