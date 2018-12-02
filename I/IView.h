//
// Created by Dordovel on 11/11/2018.
//

#ifndef UNTITLED3_IVIEW_H
#define UNTITLED3_IVIEW_H

class IView
{
public:

    virtual ~IView(){};

    virtual void printErrorCode(long)=0;

    virtual void init()=0;

    virtual bool getFlagEventShow()=0;

    virtual void invertFlagEventShow()=0;

    virtual char*getMessage()=0;

    virtual void show(char* )=0;

    virtual bool getOpenWindowFlag()=0;

};



#endif //UNTITLED3_IVIEW_H
