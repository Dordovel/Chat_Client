
#include "C/Controller.h"
#include "N/Client.h"
#include "View/View.h"

#if(__linux__)

#include<X11/Xlib.h>

#endif

class Thread
{

public:

    static void* a(void* param)
    {
        Controller * controll = (Controller *)param;
        controll->init();
        pthread_exit(0);
    }
};


int main (int argc, char **argv)
{

#if(__linux__)

    if(!XInitThreads())return 0;

#endif

#if (_WIN32)

  Controller* controller = new Controller(new View("../Uns.glade"),new Client((char*)"127.0.0.1",6000));

#endif

    if(controller)
    {

        if (controller->connection())
        {

            pthread_t thread;

            pthread_attr_t attr;

            pthread_attr_init(&attr);

            pthread_create(&thread, &attr,
                           Thread::a, controller);

            std::this_thread::sleep_for(std::chrono::milliseconds(60));

            controller->listenning();

            delete controller;
        }
    }

    return 0;

}