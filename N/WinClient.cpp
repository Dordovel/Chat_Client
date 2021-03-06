//
// Created by Dordovel on 09.10.2018.
//

#include "Client.h"

#ifdef _WIN32

Client::Client(char * address,int port)
{
    this->port=port;
    this->address=address;

    time.tv_sec=15;
    time.tv_usec=0;
};

bool Client::startClient()
{

    if (!FAILED (WSAStartup(WINSOCK_VERSION,&data)))
    {
        if ( INVALID_SOCKET == ( sock = socket( AF_INET, SOCK_STREAM, 0 ) ) )
        {
            errorCode=WSAGetLastError();
            return false;
        }
        else
        {
            addr_in.sin_family = AF_INET;
            //inet_pton( AF_INET, "127.0.0.1", &( addr_in.sin_addr));
            addr_in.sin_addr.S_un.S_addr=inet_addr(address);
            addr_in.sin_port = htons( port );

            std::cout << "Client Start" << std::endl;

        }

    }
    else
    {
        errorCode=WSAGetLastError();
        WSACleanup();
        return false;
    }

    return true;

}


bool Client::connection()
{

    if ( SOCKET_ERROR == ( connect( sock, ( sockaddr* ) &addr_in, sizeAddr_in ) ) )
    {
        errorCode=WSAGetLastError();
        closesocket( sock );
        return false;
    }

    return true;
}
bool Client::send_message(char * message)
{
    if (SOCKET_ERROR == (send(sock, message, MAX_SIZE, 0)))
    {
        errorCode = WSAGetLastError();
        closesocket(sock);

        return false;
    }
    return true;

}

bool Client::write_message()
{
    FD_ZERO(&set);
    FD_SET(sock,&set);

    if(select(sock+1,&set,NULL,NULL,&time)>0)
    {

        if (FD_ISSET(sock, &set))
        {
            FD_CLR(sock, &set);

            if (SOCKET_ERROR == (recv(sock, buffer, MAX_SIZE, 0)))
            {
                errorCode = WSAGetLastError();
                closesocket(sock);
                return false;
            }
        }
    }

   return true;

}

char * Client::getResponse()
{
    return buffer;
}

long Client::getErrorCode()
{
    return errorCode;
}


char* Client::getHostProperties()
{
    return host->h_name;
}

Client::~Client()
{
    WSACleanup();
    closesocket( sock );
}

#endif