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
    std::string GetNtBuffer(int n) const;
    std::string GetCurrentBuffer() const;
    std::string GetNtFileName(int n) const;
    std::string GetCurrentFileName() const;

    void OpenNewTab(const std::string& filename = "new");
    int AddNewTab(const std::string& filename = "new");

    void RemoveCurrentPage();
    void RemovePage(int pagenum);
private:
    std::vector<page_mem> m_pageData;

    int PageNumber(ClosableTab* tab);
};

#endif
