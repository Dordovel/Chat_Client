//
// Created by Dordovel on 10/31/2018.
//

#ifndef UNTITLED_ICLIENT_H
#define UNTITLED_ICLIENT_H


class IClient
{

public:

    virtual ~IClient(){};

    virtual bool connection()=0;

    virtual bool send_message(char *message)=0;

    virtual bool write_message()=0;

    virtual bool startClient()=0;

    virtual long getErrorCode()=0;

    virtual char* getResponse()=0;

};


#endif //UNTITLED_ICLIENT_H
