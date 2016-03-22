#include<string>

#define MAX_CMD_COUNT 5

class MainWindow;

class CommandHandler {
public:
    CommandHandler(MainWindow* window);

    void ExecuteCommand(std::string command);
private:
    std::string* ParseCommand(std::string command);

    MainWindow* m_window;
};
