#ifndef SCROLL_TEXT_H
#define SCROLL_TEXT_H

#include <gtkmm.h>

class ScrollableText : public Gtk::Box
{
public:
    ScrollableText();
    Glib::RefPtr<const Gtk::TextBuffer> get_buffer() const;
    Glib::RefPtr<Gtk::TextBuffer> get_buffer();
protected:
    Gtk::ScrolledWindow m_scrollWindow;
    Gtk::TextView m_textView;
};

#endif
