#ifndef SCROLL_TEXT_H
#define SCROLL_TEXT_H

#include <gtkmm.h>
#include <gtksourceviewmm.h>

class ScrollableText : public Gtk::Box
{
public:
    ScrollableText();
    Glib::RefPtr<const Gsv::Buffer> get_buffer() const;
    Glib::RefPtr<Gsv::Buffer> get_buffer();
protected:
    Gtk::ScrolledWindow m_scrollWindow;
    Gsv::View m_textView;
};

#endif
