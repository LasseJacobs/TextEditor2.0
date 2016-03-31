
#include "memorynotebook.h"
#include "scrollabletext.h"
#include "closabletab.h"


MemoryNotebook::~MemoryNotebook()
{
    for(unsigned int i = 0; i < pageData.size(); i++)
    {
        delete pageData[i].scrollText;
        delete pageData[i].closableTab;
    }
}


void MemoryNotebook::AddNewTab(const char* filename)
{
    ScrollableText* scrollText = new ScrollableText;
    ClosableTab* closableTab = new ClosableTab(filename, this);

    append_page( *scrollText, *closableTab);

    //push the data to pages stack
    page_mem tempMem = { scrollText, closableTab};
    pageData.push_back(tempMem);

    show_all();
}

void MemoryNotebook::OpenNewTab(const char* filename)
{
    AddNewTab(filename);
    int latestPage = get_n_pages() - 1;
    set_current_page(latestPage);

    show_all();
}


//Interface
void MemoryNotebook::SetCurrentBuffer(  const std::string& filename,
                                        const std::string& content)
{
    //Creating a new tab
    OpenNewTab(filename.c_str());
    //Setting the buffer
    Glib::ustring tempString(content);
    int currentPage = get_current_page();
    Glib::RefPtr<Gtk::TextBuffer> currentBuffer
                = pageData[currentPage].scrollText->get_buffer();

    currentBuffer->set_text(tempString);
}

std::string MemoryNotebook::GetCurrentBuffer() const
{
    int currentPage = get_current_page();
    const Glib::RefPtr<Gtk::TextBuffer> currentBuffer
                = pageData[currentPage].scrollText->get_buffer();
    Glib::ustring tempString = currentBuffer->get_text();

    return Glib::locale_from_utf8(tempString);
}

std::string MemoryNotebook::GetCurrentFileName() const
{
    int currentPage = get_current_page();
    const Glib::ustring filename
                = pageData[currentPage].closableTab->get_tab_label_text();

    return Glib::locale_from_utf8(filename);
}

void MemoryNotebook::RemovePage(int pagenum)
{
    remove_page(pagenum);

    delete pageData[pagenum].scrollText;
    delete pageData[pagenum].closableTab;

    pageData.erase(pageData.begin() + pagenum);
}

int MemoryNotebook::PageNumber(ClosableTab* tab)
{
    for(unsigned int i = 0; i < pageData.size(); i++)
    {
        if(pageData[i].closableTab == tab)
            return i;
    }
    return -1;
}
