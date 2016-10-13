
#include "closecommand.h"
#include "../mainwindow.h"

CloseCommand::CloseCommand(int pageIndex)
{
    m_pageIndex = pageIndex;
}

void CloseCommand::Execute()
{
    MemoryNotebook* notebook = MainWindow::Instance()->GetNotebook();

    if(m_pageIndex)
    {
        m_fileName = notebook->GetNtFileName(m_pageIndex);
        m_fileContent = notebook->GetNtBuffer(m_pageIndex);

        notebook->RemovePage(m_pageIndex);
    }
    else
    {
        m_fileName = notebook->GetCurrentFileName(m_pageIndex);
        m_fileContent = notebook->GetCurrentBuffer(m_pageIndex);

        notebook->RemoveCurrentPage(m_pageIndex);
    }
}

void CloseCommand::Undo()
{
    //TODO
}
