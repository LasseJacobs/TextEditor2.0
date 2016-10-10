
#include <iostream>
#include "../mainwindow.h"
#include "commandhandler.h"

#define CMD_NOT_FOUND "Command not found..."

CommandHandler::CommandHandler(MainWindow* window)
{
    m_window = window;
}

void CommandHandler::ExecuteCommand(std::string command)
{
    std::string* parsedCommand = ParseCommand(command);
    InterpretCommand(parsedCommand);
}

std::string* CommandHandler::ParseCommand(std::string command)
{
    std::string* parsedCommand = new std::string[MAX_CMD_COUNT];
    std::string delimiter = " ";

    size_t pos = 0;
    std::string token;
    int i = 0;
    while ((pos = command.find(delimiter)) != std::string::npos && i < MAX_CMD_COUNT) {
        token = command.substr(0, pos);
        parsedCommand[i++] = token;
        command.erase(0, pos + delimiter.length());
    }
    parsedCommand[i] = command;

    return parsedCommand;
}

void CommandHandler::InterpretCommand(std::string* parsedCommand)
{
    if(parsedCommand[0] == "Save")
    {
        SaveClass(&parsedCommand[1]);
    }
    else if(parsedCommand[0] == "Open")
    {
        OpenClass(&parsedCommand[1]);
    }
    else if(parsedCommand[0] == "New")
    {
        NewClass(&parsedCommand[1]);
    }
    else if(parsedCommand[0] == "Clear")
    {
        ClearClass(&parsedCommand[1]);
    }
    else if(parsedCommand[0] == "Close")
    {
        CloseClass(&parsedCommand[1]);
    }
    else
    {
        m_window->ErrorLog(CMD_NOT_FOUND);
    }
}


void CommandHandler::SaveClass(std::string* parsedCommand)
{
    std::string fileName = m_window->GetCurrentFileName();
    std::string content = m_window->GetCurrentBuffer();

    if(parsedCommand[0] == "As")
    {
        if(parsedCommand[1] == "")
        {
            m_window->ErrorLog("Please give a filename");
            return;
        }
        fileName = parsedCommand[1];
    }
    else
    {
        fileName = m_window->GetCurrentFileName();
        if(fileName == "new")
        {
            m_window->ErrorLog("Please specify a filename");
        }
    }

    if(m_iomanager.SaveFile(fileName, content))
        m_window->Log("Save Succeful");
    else
        m_window->ErrorLog("Save Failed");
}

void CommandHandler::OpenClass(std::string* parsedCommand)
{
    if(parsedCommand[0] == "")
    {
        m_window->ErrorLog("Please give a filename");
        return;
    }
    else
    {
        std::string content = m_iomanager.OpenFile(parsedCommand[0]);
        if(content != "")
        {
            m_window->Log("Open File Succeful");
            m_window->SetCurrentBuffer(parsedCommand[0], content);
        }
        else
            m_window->ErrorLog("Open File Failed");
    }
}

void CommandHandler::NewClass(std::string* parsedCommand)
{
    if(parsedCommand[0] == "File")
    {
        m_window->SetCurrentBuffer("new", "");
    }
    else
        m_window->ErrorLog(CMD_NOT_FOUND);
}

void CommandHandler::ClearClass(std::string* parsedCommand)
{
    if(parsedCommand[0] == "Status")
        m_window->Log("");
    else
        m_window->ErrorLog(CMD_NOT_FOUND);
}

void CommandHandler::CloseClass(std::string* parsedCommand)
{
    if(parsedCommand[0] == "File")
    {
        m_window->GetNotebook()->RemoveCurrentPage();
    }
    else
        m_window->ErrorLog(CMD_NOT_FOUND);
}
