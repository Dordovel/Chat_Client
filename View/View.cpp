//
// Created by Dordovel on 11/11/2018.
//

#include <iostream>
#include <thread>
#include "View.h"

View::View(std::string fileGladePath):p_tree_view(nullptr),
             p_button(nullptr),
             window(nullptr),
             message("")
{
    flagEventShow = false;

    app=Gtk::Application::create();

    builder = Gtk::Builder::create();

    try
    {
        builder->add_from_file(fileGladePath);

    }
    catch (const Glib::FileError & ex)
    {
        std::cerr <<"Error "<<ex.what()<<std::endl;
    }

    findViewById();

}

View::~View()
{

    if(window!= nullptr)
    {
        delete window;
        window= nullptr;
    }

    if(p_tree_view!= nullptr)
    {
        delete p_tree_view;
        p_tree_view= nullptr;
    }

    if(p_text_entry!= nullptr)
    {
        delete p_text_entry;
        p_text_entry= nullptr;
    }


    if(p_button!= nullptr)
    {
        delete p_button;
        p_button= nullptr;
    }
}

void View::findViewById()
{
    builder->get_widget("button1",p_button);

    builder->get_widget("entry1",p_text_entry);

    builder->get_widget("treeView1",p_tree_view);

    builder->get_widget("MainWindow",window);
}


void View::init()
{
    if(window)
    {

        window->set_title("GTK");

        window->set_default_size(300,300);

        listStore=Gtk::ListStore::create(model);

        p_tree_view->set_model(listStore);

        p_tree_view->append_column("Messages",model.m_col);

        window->signal_hide().connect(sigc::mem_fun(this,&View::closeWindow));

        p_text_entry->signal_activate().connect(sigc::mem_fun(this,&View::event));

        if(p_button)
        {
            p_button->signal_clicked().connect(sigc::mem_fun(this, &View::event));
        }

        openWindowFlag=true;

        app->run(*window);
    }
}

void View::closeWindow()
{
    this->openWindowFlag=false;
}


void View::event()
{

    if(p_text_entry->get_text()!="")
    {
        flagEventShow=true;

        this->message=(char*)p_text_entry->get_text().c_str();

    }
    p_text_entry->set_placeholder_text("Enter your message");

}


void View::show(char * str)
{

    row = *(listStore->append());

    row[model.m_col] = str;

    p_text_entry->set_text("");

}


void View::printErrorCode(long i)
{
    std::cerr<<i<<std::endl;
}

bool View::getFlagEventShow()
{
    return  flagEventShow;
}

void View::invertFlagEventShow()
{
    if(flagEventShow)
    {
        flagEventShow=false;
    }
}

char *View::getMessage()
{
    return (char* )this->message.c_str();
}

bool View::getOpenWindowFlag()
{
    return openWindowFlag;
}
