#ifndef NEWF_CMD_H
#define NEWF_CMD_H

#include "command.h"
#include <string>

class NewFileCommand : public Command {
public:
    NewFileCommand(const std::string& filename, const std::string& content = "");

    void Execute();
    void Undo();

private:
    std::string m_filename;
};

#endif
