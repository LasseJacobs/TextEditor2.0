
#include "closabletab.h"


ClosableTab::ClosableTab(const std::string& name, MemoryNotebook* parent)
        : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL)
{
    m_parent = parent;
    CreateUI(name);
}

const Glib::ustring ClosableTab::get_tab_label_text() const
{
    return m_caption.get_text();
}

void ClosableTab::CreateUI(const std::string& name)
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
    //TODO test this might need to good to PageNumber
    int pageNumber = m_parent->page_num(*this);
    m_parent->RemovePage(pageNumber);
}
