#include <iostream>
#include <fstream>
#include "fileio.h"

bool FileIO::SaveFile(std::string filename, std::string content)
{
    std::ofstream saveFile(filename.c_str());
    if (saveFile.is_open())
    {
        saveFile << content;
        saveFile.close();
    }
    else
    {
        return false;
    }

    return true;
}

std::string FileIO::OpenFile(std::string filename)
{
    std::ifstream saveFile(filename.c_str());

    std::string content;
    std::string line;

    if (saveFile.is_open())
    {
        while(getline(saveFile, line))
        {
            content += line;
            content.push_back('\n');
        }
        saveFile.close();
    }
    else
    {
        return "";
    }

    return content;
}
