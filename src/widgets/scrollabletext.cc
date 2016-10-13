
#include "scrollabletext.h"


ScrollableText::ScrollableText( const std::string& filename,
                                const std::string& content)
{
    Gsv::init();

    SetBufferText("main.c", content);

    m_textView.set_show_line_numbers(true);
    m_scrollWindow.add(m_textView);

    //Only show the scrollbars when they are necessary:
    m_scrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    pack_start(m_scrollWindow);
}


//New interface
void ScrollableText::SetBufferText( const std::string& filename,
                                    const std::string& content)
{
    Glib::RefPtr<Gsv::LanguageManager> language_manager
                                        = Gsv::LanguageManager::get_default();

    Glib::RefPtr<Gsv::Language> language =
                            language_manager->guess_language(filename, "");

    Glib::RefPtr<Gsv::Buffer> buffer = Gsv::Buffer::create(language);
    buffer->set_text(content);
    m_textView.set_source_buffer(buffer);
}

std::string ScrollableText::GetBufferText() const
{
    Glib::ustring tempString = m_textView.get_source_buffer()->get_text();

    return Glib::locale_from_utf8(tempString);
}
