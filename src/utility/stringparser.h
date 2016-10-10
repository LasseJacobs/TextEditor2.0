#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <vector>

class StringParser {
public:
    std::vector<std::string> ParseString(const std::string& command);

private:
    void Split(std::vector<std::string> &elems, const std::string& s, char delim);
};

#endif
