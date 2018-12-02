//
// Created by Dordovel on 11/11/2018.
//

#ifndef UNTITLED3_VIEW_H
#define UNTITLED3_VIEW_H

#include "../I/IView.h"
#include<gtkmm-3.0/gtkmm.h>
#include "../ModelColums.h"

class View :public IView
{

    Glib::RefPtr<Gtk::Builder> builder;

    Gtk::Entry *p_text_entry;

    Glib::RefPtr<Gtk::ListStore> listStore;

    Gtk::TreeModel::Row row;

    ModelColums model;

    Glib::RefPtr<Gtk::Application> app;

    Gtk::TreeView *p_tree_view;

    Gtk::Button *p_button;

    Gtk::Window *window;

    bool flagEventShow;

    bool openWindowFlag;

    void event();

    void findViewById();

    void closeWindow();

    std::string message;

public:

     View(std::string fileGladePath);

    ~View() override;

    void printErrorCode(long i) override;

    bool getFlagEventShow() override;

    void invertFlagEventShow() override;

    void init() override;

    char *getMessage() override;

    void show(char*) override;

    bool getOpenWindowFlag() override;

};

#endif //UNTITLED3_VIEW_H
