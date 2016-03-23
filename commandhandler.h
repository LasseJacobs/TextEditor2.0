#ifndef CMD_HNDLER
#define CMD_HNDLER

#include "fileio.h"
#include<string>

#define MAX_CMD_COUNT 5

class MainWindow;

class CommandHandler {
public:
    CommandHandler(MainWindow* window);

    void ExecuteCommand(std::string command);
private:
    std::string* ParseCommand(std::string command);
    void InterpretCommand(std::string* parsedCommand);

    MainWindow* m_window;
    FileIO m_iomanager;
};

#endif
