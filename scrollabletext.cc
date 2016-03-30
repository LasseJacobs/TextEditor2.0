
#include "scrollabletext.h"

ScrollableText::ScrollableText()
{
    m_scrollWindow.add(m_textView);

    //Only show the scrollbars when they are necessary:
    m_scrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    pack_start(m_scrollWindow);
}

Glib::RefPtr<const Gtk::TextBuffer> ScrollableText::get_buffer() const
{
    return m_textView.get_buffer();
}

Glib::RefPtr<Gtk::TextBuffer> ScrollableText::get_buffer()
{
    return m_textView.get_buffer();
}
