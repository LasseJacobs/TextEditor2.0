
#include <iostream>
#include"commandhandler.h"

CommandHandler::CommandHandler(MainWindow* window)
{
    m_window = window;
}

void CommandHandler::ExecuteCommand(std::string command)
{
    std::string* cmd = ParseCommand(command);

    for(int i = 0; i < MAX_CMD_COUNT; i++)
        std::cout << cmd[i] << std::endl;
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
