
#include "scrollabletext.h"

ScrollableText::ScrollableText()
{
    Gsv::init();

    Glib::RefPtr<Gsv::LanguageManager> language_manager
                                        = Gsv::LanguageManager::get_default();
    //TODO: make this an option to choose syntax highlighting
    Glib::RefPtr<Gsv::Language> language = language_manager->get_language("c");

    Glib::RefPtr<Gsv::Buffer> buffer = Gsv::Buffer::create(language);
    buffer->set_text("");
    m_textView.set_source_buffer(buffer);

    m_scrollWindow.add(m_textView);

    //Only show the scrollbars when they are necessary:
    m_scrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    pack_start(m_scrollWindow);
}

Glib::RefPtr<const Gsv::Buffer> ScrollableText::get_buffer() const
{
    return m_textView.get_source_buffer();
}

Glib::RefPtr<Gsv::Buffer> ScrollableText::get_buffer()
{
    return m_textView.get_source_buffer();
}
