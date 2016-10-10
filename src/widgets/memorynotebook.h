#ifndef MEM_NBOOK_H
#define MEM_NBOOK_H

#include <gtkmm.h>
#include <vector>
#include "pagemem.h"

class MemoryNotebook : public Gtk::Notebook
{
public:
    ~MemoryNotebook();

    //Interface
    void SetCurrentBuffer(const std::string& filename, const std::string& content);
    std::string GetCurrentBuffer() const;
    std::string GetCurrentFileName() const;

    void AddNewTab(const char* filename = "new");
    void OpenNewTab(const char* filename = "new");

    void RemoveCurrentPage();
    void RemovePage(int pagenum);
    int PageNumber(ClosableTab* tab);
protected:
    std::vector<page_mem> m_pageData;
};

#endif
