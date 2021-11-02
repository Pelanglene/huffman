//
// Created by ulad on 06.10.2021.
//

#ifndef ARCHIEVER_PARSER_H
#define ARCHIEVER_PARSER_H

#include <vector>

class Parser {
public:
    void ParseFlags(int argc, char* argv[], std::vector<std::string> &filenames, std::string &name);
    static void PrintHelp();
    Parser();
    bool Option() const;
private:
    bool archive;
};


#endif //ARCHIEVER_PARSER_H
