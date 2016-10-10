#ifndef FILE_IO_HEADER
#define FILE_IO_HEADER

#include <string>

class FileIO{
public:
    bool SaveFile(std::string filename, std::string content);
    std::string OpenFile(std::string filename);
};

#endif
