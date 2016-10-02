#ifndef CMD_HNDLER
#define CMD_HNDLER

#include "fileio.h"
#include<string>

#define MAX_CMD_COUNT 5

class MainWindow;

//TODO: This whole class needs to change for cleaner code
class CommandHandler {
public:
    CommandHandler(MainWindow* window);

    void ExecuteCommand(std::string command);
private:
    std::string* ParseCommand(std::string command);
    void InterpretCommand(std::string* parsedCommand);

    //Commands
    void SaveClass(std::string* parsedCommand);
    void OpenClass(std::string* parsedCommand);
    void NewClass(std::string* parsedCommand);
    void ClearClass(std::string* parsedCommand);
    void CloseClass(std::string* parsedCommand);

    MainWindow* m_window;
    FileIO m_iomanager;
};

#endif
