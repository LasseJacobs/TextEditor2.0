
#include "memorynotebook.h"
#include "scrollabletext.h"
#include "closabletab.h"


MemoryNotebook::~MemoryNotebook()
{
    for(unsigned int i = 0; i < m_pageData.size(); i++)
    {
        delete m_pageData[i].scrollText;
        delete m_pageData[i].closableTab;
    }
}

void MemoryNotebook::OpenNewTab(const std::string& filename,
                                const std::string& content)
{
    AddNewTab(filename, content);
    int latestPage = get_n_pages() - 1;
    set_current_page(latestPage);

    show_all();
}

int MemoryNotebook::AddNewTab(  const std::string& filename,
                                const std::string& content)
{
    ScrollableText* scrollText = new ScrollableText(filename, content);
    ClosableTab* closableTab = new ClosableTab(filename, this);

    append_page( *scrollText, *closableTab);
    set_tab_reorderable(*scrollText);

    //push the data to pages stack
    page_mem tempMem = { scrollText, closableTab};
    m_pageData.push_back(tempMem);

    show_all();

    //TODO do we really need this??
    return page_num(*closableTab);
}


//Interface
void MemoryNotebook::SetCurrentBuffer(  const std::string& filename,
                                        const std::string& content)
{
    //Setting the buffer
    Glib::ustring tempString(content);
    int currentPage = get_current_page();
    m_pageData[currentPage].scrollText->SetBufferText(filename, content);
}

std::string MemoryNotebook::GetCurrentBuffer() const
{
    int currentPage = get_current_page();

    return m_pageData[currentPage].scrollText->GetBufferText();
}

std::string MemoryNotebook::GetNtBuffer(int n) const
{
    return m_pageData[n].scrollText->GetBufferText();
}

std::string MemoryNotebook::GetCurrentFileName() const
{
    int currentPage = get_current_page();
    const Glib::ustring filename
                = m_pageData[currentPage].closableTab->get_tab_label_text();

    return Glib::locale_from_utf8(filename);
}

std::string MemoryNotebook::GetNtFileName(int n) const
{
    const Glib::ustring filename
                = m_pageData[n].closableTab->get_tab_label_text();

    return Glib::locale_from_utf8(filename);
}

void MemoryNotebook::RemoveCurrentPage()
{
    int p_index = get_current_page();
    RemovePage(p_index);
}

//TODO virtual to parent if possible??
void MemoryNotebook::RemovePage(int pagenum)
{
    remove_page(pagenum);

    delete m_pageData[pagenum].scrollText;
    delete m_pageData[pagenum].closableTab;

    m_pageData.erase(m_pageData.begin() + pagenum);
}


/*
int MemoryNotebook::PageNumber(ClosableTab* tab)
{
    for(unsigned int i = 0; i < m_pageData.size(); i++)
    {
        if(m_pageData[i].closableTab == tab)
            return i;
    }
    return -1;
}
*/
