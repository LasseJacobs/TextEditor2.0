
#include <iostream>
#include"mainwindow.h"
#include"commandhandler.h"

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
        std::string fileName = m_window->GetCurrentFileName();
        std::string content = m_window->GetCurrentBuffer();

        if(parsedCommand[1] == "As")
        {
            if(parsedCommand[2] == "")
            {
                m_window->ErrorLog("Please give a file name");
                return;
            }
            fileName = parsedCommand[2];
        }
        else
        {
            fileName = m_window->GetCurrentFileName();
        }

        if(m_iomanager.SaveFile(fileName, content))
            m_window->Log("Save Succeful");
        else
            m_window->ErrorLog("Save Failed");
    }
    else if(parsedCommand[0] == "Open")
    {
        if(parsedCommand[1] == "")
        {
            m_window->ErrorLog("Please give a file name");
            return;
        }
        else
        {
            std::string content = m_iomanager.OpenFile(parsedCommand[1]);
            if(content != "")
            {
                m_window->Log("Open File Succeful");
                m_window->SetCurrentBuffer(content);
            }
            else
                m_window->ErrorLog("Open File Failed");
        }
    }
    else if(parsedCommand[0] == "Clear")
    {
        if(parsedCommand[1] == "Status")
            m_window->Log("");
        else
            m_window->ErrorLog("SaveFailed");
    }
    else
    {
        m_window->ErrorLog("Command not found...");
    }
}
