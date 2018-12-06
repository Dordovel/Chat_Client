//
// Created by Dordovel on 09.10.2018.
//

#include "Client.h"

#ifdef  __linux__

Client::Client(char * address,int port)
{
    this->port=port;
    this->address=address;
};


bool Client::startClient()
{
    if((sockID=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        errorCode=sockID;
        return false;
    }
    else
    {
        bzero(&addr_in,sizeAddr_in);
        std::cout<<"Socket invalid"<<std::endl;

        host=gethostbyname(address);

        addr_in.sin_port=htons(port);
        addr_in.sin_family=AF_INET;
        bcopy((char*)host->h_addr,(char*)&addr_in.sin_addr.s_addr,host->h_length);

    }
    return true;
}

bool Client::connection()
{
        if ((errorCode=connect(sockID, (struct sockaddr *) &addr_in, sizeAddr_in) )< 0)
        {
            return false;
        }
        else
        {
            std::cout << "Connection Ok" << std::endl;
        }

    return true;

}

bool Client::write_message()
{
    fd_set set;
    int iof;

    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(sockID, &set);

    tv.tv_sec = 0;
    tv.tv_usec = 7000;

    if (select(sockID + 1, &set, NULL, NULL, &tv)>0 && FD_ISSET(sockID,&set))
    {

        if((iof=fcntl(sockID,F_GETFL,0)!=0))
        {
            fcntl(sockID, F_SETFL, iof, O_NONBLOCK);
        }

            if ((errorCode = recv(sockID, buffer, 20, 0)) <= 0)
            {
                return false;
            }

        if(iof!=-1)
        {
            fcntl(sockID,F_SETFL,iof);
        }

    } else
     {
         return false;
    }

    return true;

}

bool Client::send_message(char * msg)
{
    return (errorCode=send(sockID,msg,20,0))>0;
}

char * Client::getResponse()
{
    return buffer;
}

long Client::getErrorCode()
{
    return errorCode;
}

Client::~Client() {}

#endif