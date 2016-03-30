#ifndef CLOSE_TAB_H
#define CLOSE_TAB_H

#include <gtkmm.h>

class ClosableTab : public Gtk::Box
{
public:
    ClosableTab(const char* name, Gtk::Notebook* parent);

    const Glib::ustring get_tab_label_text() const;
protected:
    Gtk::Label m_caption;
    Gtk::Button m_closeButton;
    Gtk::Notebook* m_parent;

    bool m_active;

    void CreateUI(const char* name);
    void OnButtonClicked();
};

#endif
