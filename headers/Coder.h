//
// Created by ulad on 05.10.2021.
//

#ifndef ARCHIEVER_CODER_H
#define ARCHIEVER_CODER_H

#include <vector>
#include <unordered_map>
#include "Getter.h"
#include "Putter.h"

class Coder {
public:
    Coder();

    void MakeTable(Getter &read, const std::string& filename);

    void Code(const std::string &filename, Getter &read, Putter &write, bool isArchiveEnd);

private:
    std::vector<int64_t> table;
    std::unordered_map<int16_t, std::string> CodeTable;
    int16_t SymbolCount;
    std::vector<int16_t> canonical;

};


#endif //ARCHIEVER_CODER_H
