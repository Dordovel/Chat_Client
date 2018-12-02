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

#define SOCKET int
#define WSAData void*

#endif


class Client:public IClient
{
    WSAData data;
    SOCKET sock;
    sockaddr_in addr_in;
    int port = 6000;
    int sizeAddr_in = sizeof( addr_in );
    int sockID;
    hostent *host;
    long errorCode=0;

    char buffer[20];

public:
    Client();
    ~Client();

    bool connection() override;
    bool send_message(char *message) override;
    bool write_message() override;
    bool startClient() override;
    long getErrorCode() override;
    char* getResponse() override;

};

#endif //UNTITLED_CLIENT_H
