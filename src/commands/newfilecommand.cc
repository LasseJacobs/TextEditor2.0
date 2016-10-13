
#include "newfilecommand.h"
#include "mainwindow.h"

NewFileCommand::NewFileCommand( const std::string& filename,
                                const std::string& content)
{
    m_filename = filename;
}

void NewFileCommand::Execute()
{
    MainWindow* mwindow = MainWindow::Instance();
    mwindow->GetNotebook()->OpenNewTab(filename);
}

void NewFileCommand::Undo()
{
    //No undo supported
    return;
}
