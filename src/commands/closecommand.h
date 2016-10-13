#ifndef CLOSE_CMD_H
#define CLOSE_CMD_H

#include <string>

class CloseCommand {
public:
    CloseCommand(int pageIndex = 0);
    void Execute();
    void Undo();

private:
    int m_pageIndex;

    std::string m_fileContent;
    std::string m_fileName;
};

#endif
