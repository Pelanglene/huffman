//
// Created by ulad on 06.10.2021.
//

#include <iostream>
#include "headers/Parser.h"
#include "headers/config.h"

Parser::Parser() {
    archive = false;
}

void Parser::PrintHelp() {
    std::cout << "using: \n";
    std::cout << "archiver -c archive_name file1 [file2 ...] - archive files fil1, file2, ... ";
    std::cout << "and save result to file archive_name.\n";
    std::cout << "archiver -d archive_name - unarchive files from file";
    std::cout << "archive_name and put it to current directory.";
    std::cout << "\n";
    std::cout << "archiver -h - help.\n";
}

void Parser::ParseFlags(int argc, char* argv[], std::vector<std::string> &filenames, std::string &name) {
    if (argc == 1) {
        throw PARSER_ERROR;
    }
    if (static_cast<std::string>(argv[1]) == "-c") {
        if (argc < 4) {
            throw PARSER_ERROR;
        }
        std::cout << "archive name: " << argv[2] << "\n";
        name = argv[2];
        for (size_t i = 3; i < argc; ++i) {
            std::cout << "filename " << i - 3 << ": " << argv[i] << "\n";
            filenames.emplace_back(argv[i]);
        }
        archive = true;
        return;
    }
    if (static_cast<std::string>(argv[1]) == "-d") {
        if (argc < 3) {
            throw PARSER_ERROR;
        }
        std::cout << "archive name: " << argv[2] << "\n";
        name = argv[2];
        return;
    }
    Parser::PrintHelp();
    return;
}

bool Parser::Option() const {
    return this->archive;
}