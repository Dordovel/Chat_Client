//
// Created by Dordovel on 11/12/2018.
//

#ifndef UNTITLED3_CONTOLLER_H
#define UNTITLED3_CONTOLLER_H

#include "../N/Client.h"
#include "../View/View.h"

#include<thread>

class Controller
{

private:
    IView *view;
    IClient * file;

    std::string message;


public:
    Controller(IView * view,IClient *file);

    ~Controller();

    void init();

     void listenning();

     bool connection();

};


#endif //UNTITLED3_CONTOLLER_H
