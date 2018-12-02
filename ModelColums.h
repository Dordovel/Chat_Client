//
// Created by Dordovel on 11/11/2018.
//

#ifndef UNTITLED3_MODELCOLUMS_H
#define UNTITLED3_MODELCOLUMS_H


#include <gtkmm/treemodel.h>

class ModelColums : public Gtk::TreeModel::ColumnRecord
{

public:
    Gtk::TreeModelColumn<Glib::ustring> m_col;

    ModelColums()
    {
        add(m_col);
    }

};


#endif //UNTITLED3_MODELCOLUMS_H
