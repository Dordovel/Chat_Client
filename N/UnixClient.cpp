//
// Created by Dordovel on 09.10.2018.
//

#include "Client.h"

#ifdef  __linux__

Client::Client(char * address,int port)
{
    this->port=port;
    this->address=address;

    time.tv_sec=15;
    time.tv_usec=0;
};


bool Client::startClient()
{
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        errorCode=sock;
        return false;
    }
    else
    {
        bzero(&addr_in,sizeAddr_in);
        std::cout<<"Socket invalid"<<std::endl;

        host=gethostbyname(address);

        if(host)
        {
            addr_in.sin_port = htons(port);
            addr_in.sin_family = AF_INET;
            bcopy((char *) host->h_addr, (char *) &addr_in.sin_addr.s_addr, host->h_length);

        } else
            {
            std::cout<<"Host not Found"<<std::endl;
        }

    }
    return true;
}

bool Client::connection()
{
        if ((errorCode=connect(sock, (struct sockaddr *) &addr_in, sizeAddr_in) )< 0)
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
    FD_ZERO(&set);
    FD_SET(sock,&set);

        if(select(sock+1,&set,NULL,NULL,&time)>0)
        {

            if(FD_ISSET(sock,&set))
            {
                FD_CLR(sock, &set);

                if ((errorCode = recv(sock, buffer, MAX_SIZE, 0)) <= 0)
                {
                    return false;
                }
            }
    }
    return true;
}

bool Client::send_message(char * msg)
{
    return (errorCode=send(sock,msg,MAX_SIZE,0))>0;
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
    close(sock);
}

#endif