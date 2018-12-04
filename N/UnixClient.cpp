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
    std::cout<<"Binding"<<std::endl;

    if((errorCode=bind(sockID,(struct sockaddr *)&addr_in,sizeAddr_in))<0)
    {
        return false;
    }
    else
    {
        std::cout << "Bind Ok" << std::endl;

        if ((errorCode=connect(sockID, (struct sockaddr *) &addr_in, sizeAddr_in) )< 0)
        {
            return false;
        }
        else
        {
            std::cout << "Connection Ok" << std::endl;
        }
    }


    return true;

}

bool Client::write_message()
{
    return (errorCode=recv(sockID,buffer,20,0))>0;
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