//
// Created by Dordovel on 11/12/2018.
//

#include "Controller.h"


Controller::Controller(IView *view, IClient *file)
{
    this->view=view;
    this->file=file;
    this->message="";

}

Controller::~Controller()
{

    if(view)
    {
        delete view;
        view= nullptr;
    }

    if(file)
    {
        delete file;
        file= nullptr;
    }


}

void Controller::init()
{
    this->view->init();

}

bool Controller::connection()
{
    if(this->file->startClient())
    {
        if(this->file->connection())
        {
            return true;
        }
        else
        {
            this->view->printErrorCode(this->file->getErrorCode());
            return false;
        }
    }
    else
    {
        this->view->printErrorCode(this->file->getErrorCode());
        return false;
    }

}

void Controller::listenning() {
    std::string temp;
    bool flag=false;

    while (true)
    {
        if (!this->view->getOpenWindowFlag())break;

        if ((flag = this->view->getFlagEventShow()))
        {
            this->view->invertFlagEventShow();
        }

        if(this->file->write_message())
        {
            temp = this->file->getResponse();

            if (temp == "request")
            {

                if (!flag)
                {
                    this->file->send_message((char *) "200");
                }
                else
                    {
                    this->file->send_message(this->view->getMessage());
                }
            } else

                {
                this->view->show((char *) temp.c_str());
            }

            std::this_thread::sleep_for(std::chrono::milliseconds( 300 ));
        }
         else
            {
                this->view->show((char*)"No response from server,Close Application? Yes/No");

                while(!this->file->write_message())
                {

                    if (this->view->getFlagEventShow())
                    {
                        if (!strcmp(this->view->getMessage(), (char*)"Yes"))
                        {
                            return;
                        }

                        else if (!strcmp(this->view->getMessage(),(char*) "No"))
                        {
                            break;
                        }

                    }
                }
            }

    }
}

