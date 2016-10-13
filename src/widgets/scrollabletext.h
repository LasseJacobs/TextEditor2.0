#ifndef SCROLL_TEXT_H
#define SCROLL_TEXT_H

#include <gtkmm.h>
#include <gtksourceviewmm.h>
#include <string>

class ScrollableText : public Gtk::Box
{
public:
    ScrollableText(const std::string& filename = "main.c",
                            const std::string& content = "");

    void SetBufferText(const std::string& filename,
                            const std::string& content = "");
    std::string GetBufferText() const;

    Glib::RefPtr<const Gsv::Buffer> get_buffer() const;
    Glib::RefPtr<Gsv::Buffer> get_buffer();
protected:
    Gtk::ScrolledWindow m_scrollWindow;
    Gsv::View m_textView;
};

#endif
