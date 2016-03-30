
#include "closabletab.h"


ClosableTab::ClosableTab(const char* name, Gtk::Notebook* parent)
        : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL)
{
    m_parent = parent;
    CreateUI(name);
}

const Glib::ustring ClosableTab::get_tab_label_text() const
{
    return m_caption.get_text();
}

void ClosableTab::CreateUI(const char* name)
{
    m_caption.set_label(name);

    m_closeButton.set_image_from_icon_name("window-close");
    m_closeButton.signal_clicked().connect( sigc::mem_fun(*this,
             &ClosableTab::OnButtonClicked) );

    pack_start(m_caption);
    pack_start(m_closeButton);
    show_all();
}

void ClosableTab::OnButtonClicked()
{
    m_parent->remove_page(m_parent->page_num(*this));
}
