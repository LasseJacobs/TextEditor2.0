#ifndef CMD_H
#define CMD_H

class Command {
public:
    void Execute() = 0;
    void Undo() = 0;
};

#endif
