
#include <string>
#include <sstream>
#include "stringparser.h"

std::vector<std::string> StringParser::ParseString(const std::string& command)
{
    std::vector<std::string> elems;
    const char delim = ' ';

    Split(elems, command, delim);
    return elems;
}

void StringParser::Split(   std::vector<std::string> &elems,
                            const std::string& s, char delim) {
    std::stringstream ss;
    ss.str(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        if(!item.empty())
            elems.push_back(item);
    }
}

#include <iostream>

int main()
{
    StringParser sp;

    std::vector<std::string> v = sp.ParseString("Hey hello   all good?");

    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;

    return 0;
}
