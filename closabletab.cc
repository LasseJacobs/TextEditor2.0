
#include "closabletab.h"


ClosableTab::ClosableTab(const char* name, Gtk::Notebook* parent)
        : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL)
{
    m_parent = parent;
    CreateUI(name);
}

void ClosableTab::CreateUI(const char* name)
{
    m_caption = new Gtk::Label(name);
    m_closeButton = new Gtk::Button();

    m_closeButton->set_image_from_icon_name("window-close");
    m_closeButton->signal_clicked().connect( sigc::mem_fun(*this,
             &ClosableTab::OnButtonClicked) );

    pack_start( *m_caption );
    pack_start( *m_closeButton );
    show_all();
    //m_close->hide();
}

void ClosableTab::OnButtonClicked()
{
    m_parent->remove_page(m_parent->page_num(*this));
}
