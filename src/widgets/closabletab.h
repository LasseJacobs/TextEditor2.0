#ifndef CLOSE_TAB_H
#define CLOSE_TAB_H

#include <gtkmm.h>
#include "memorynotebook.h"

class ClosableTab : public Gtk::Box
{
public:
    ClosableTab(const std::string& name, MemoryNotebook* parent);

    const Glib::ustring get_tab_label_text() const;
protected:
    Gtk::Label m_caption;
    Gtk::Button m_closeButton;
    MemoryNotebook* m_parent;

    bool m_active;

    void CreateUI(const std::string& name);
    void OnButtonClicked();
};

#endif
